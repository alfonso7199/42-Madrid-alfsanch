FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    mariadb-server \
    gettext-base \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# gettext-base: necesario para el comando envsubst (sustituye variables en init.sql)

# Crea el directorio del socket y asigna permisos al usuario mysql
# (evita errores de "Can't connect to local MySQL server through socket")
RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

COPY conf/my.cnf /etc/mysql/conf.d/inception.cnf
# init.sql se copia también a conf.d/ para que init_db.sh lo encuentre con envsubst
COPY conf/init.sql /etc/mysql/conf.d/init.sql
COPY tools/init_db.sh /init_db.sh
RUN chmod +x /init_db.sh

EXPOSE 3306

ENTRYPOINT ["/init_db.sh"]
