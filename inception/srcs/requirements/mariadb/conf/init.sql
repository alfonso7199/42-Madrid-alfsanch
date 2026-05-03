-- MariaDB ejecuta este archivo en el primer arranque (init-file en my.cnf).
-- Las variables ${...} son sustituidas por envsubst en el start.sh antes de pasárselo a MariaDB.

-- Establecemos contraseña del root local
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';

-- Creamos (o actualizamos) un root remoto para acceso desde otros contenedores si fuera necesario
CREATE USER IF NOT EXISTS 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
ALTER USER 'root'@'%' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';

-- Creamos la base de datos y el usuario de WordPress
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE} CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';

-- Eliminamos el usuario anónimo y la BD de test por seguridad
DELETE FROM mysql.user WHERE User='';
DROP DATABASE IF EXISTS test;

FLUSH PRIVILEGES;
