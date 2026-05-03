#!/bin/bash
set -e

DB_PASSWORD=$(cat /run/secrets/db_password)
WP_ADMIN_PASSWORD=$(cat /run/secrets/admin)
WP_USER_PASSWORD=$(cat /run/secrets/credentials)

WP_URL="https://${DOMAIN_NAME}"

cd /var/www/html

if [ ! -f wp-config.php ]; then
    echo "Creating wp-config.php..."
    wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${DB_PASSWORD}" \
        --dbhost="mariadb:3306" \
        --dbcharset="utf8mb4" \
        --allow-root
fi

echo "Waiting for MariaDB to be ready..."
until wp db check --allow-root 2>/dev/null; do
    echo "  MariaDB not ready yet, retrying in 2s..."
    sleep 2
done
echo "MariaDB is ready."

if ! wp core is-installed --allow-root 2>/dev/null; then

    echo "Installing WordPress..."
    wp core install \
        --url="${WP_URL}" \
        --title="${WP_TITLE}" \
        --admin_user="${WP_ADMIN_USER}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --skip-email \
        --allow-root

    wp option update siteurl "${WP_URL}" --allow-root
    wp option update home    "${WP_URL}" --allow-root

    echo "Creating secondary user..."
    wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
        --role=editor \
        --user_pass="${WP_USER_PASSWORD}" \
        --allow-root

    chown -R www-data:www-data /var/www/html
    echo "WordPress setup complete."
else
    echo "WordPress already installed, skipping setup."
fi

exec php-fpm8.2 -F
