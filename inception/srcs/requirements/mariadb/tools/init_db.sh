#!/bin/bash
set -e

export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
export MYSQL_PASSWORD=$(cat /run/secrets/db_password)

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB data directory..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db

    envsubst < /etc/mysql/conf.d/init.sql > /var/lib/mysql/init.sql
    chown mysql:mysql /var/lib/mysql/init.sql
    chmod 660 /var/lib/mysql/init.sql
    echo "Init SQL prepared."
fi

exec su -s /bin/bash mysql -c "mariadbd"
