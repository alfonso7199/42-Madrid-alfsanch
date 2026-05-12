#!/bin/bash
set -e

echo "[mariadb] Reading secrets..." >&2
export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
export MYSQL_PASSWORD=$(cat /run/secrets/db_password)
echo "[mariadb] Secrets loaded." >&2

chown -R mysql:mysql /var/lib/mysql

if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "[mariadb] Initializing data directory..." >&2
    mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db
    echo "[mariadb] Data directory initialized." >&2
fi

echo "[mariadb] Preparing init SQL..." >&2
envsubst < /etc/mysql/conf.d/init.sql > /var/lib/mysql/init.sql
chown mysql:mysql /var/lib/mysql/init.sql
chmod 660 /var/lib/mysql/init.sql
echo "[mariadb] Starting mariadbd..." >&2

exec mariadbd --user=mysql --bind-address=0.0.0.0
