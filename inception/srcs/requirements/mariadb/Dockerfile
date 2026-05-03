FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    mariadb-server \
    gettext-base \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld

COPY conf/my.cnf /etc/mysql/conf.d/inception.cnf

COPY conf/init.sql /etc/mysql/conf.d/init.sql
COPY tools/init_db.sh /init_db.sh
RUN chmod +x /init_db.sh

EXPOSE 3306

ENTRYPOINT ["/init_db.sh"]
