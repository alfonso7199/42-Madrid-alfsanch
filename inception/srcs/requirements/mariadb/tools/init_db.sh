#!/bin/bash
set -e

# Leemos las contraseñas desde Docker secrets (nunca hardcodeadas)
export MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
export MYSQL_PASSWORD=$(cat /run/secrets/db_password)

# Solo inicializamos si la BD no existe todavía (primer arranque)
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB data directory..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db

    # envsubst sustituye ${MYSQL_ROOT_PASSWORD}, ${MYSQL_USER}, etc. en init.sql
    # y deja el resultado en /var/lib/mysql/init.sql, que MariaDB ejecutará al arrancar
    # gracias a init-file = /var/lib/mysql/init.sql en my.cnf
    envsubst < /etc/mysql/conf.d/init.sql > /var/lib/mysql/init.sql
    chown mysql:mysql /var/lib/mysql/init.sql
    chmod 660 /var/lib/mysql/init.sql
    echo "Init SQL prepared."
fi

# Arrancamos MariaDB en primer plano como usuario mysql (PID 1 del contenedor)
exec su -s /bin/bash mysql -c "mariadbd"
