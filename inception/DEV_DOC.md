# DEV_DOC — Inception

### Prerequisites

- Docker and Docker Compose v2 installed.

### 1. Clone the repository

```bash
git clone https://github.com/alfonso7199/42-Madrid-alfsanch.git
cd 42-Madrid-alfsanch/inception
```

### 2. Create the secrets files (not tracked by git)

Both `secrets/` and `srcs/.env` are gitignored and must be created manually after cloning.

```bash
mkdir -p secrets
echo "your_db_password"    > secrets/db_password.txt
echo "your_root_password"  > secrets/db_root_password.txt
echo "your_admin_password" > secrets/admin.txt
echo "your_user_password"  > secrets/credentials.txt
echo "your_ftp_password"   > secrets/ftp_password.txt
```

### 3. Create the `.env` file

```bash
cat > srcs/.env << 'EOF'
DOMAIN_NAME=alfsanch.42.fr

MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser

WP_TITLE=Inception
WP_ADMIN_USER=alfsanch_sudo
WP_ADMIN_EMAIL=alfsanch_sudo@student.42madrid.com
WP_USER=alfsanch
WP_USER_EMAIL=alfsanch@student.42madrid.com
EOF
```

> Passwords are never stored in `.env` — they live in `secrets/` and are mounted as Docker secrets.

### 4. Configure the domain

Add this line to `/etc/hosts` on the VM:

```
127.0.0.1  alfsanch.42.fr
```

### 5. Build and launch

```bash
make
```

This will:
1. Create `/home/alfsanch/data/wordpress` and `/home/alfsanch/data/mariadb` on the host.
2. Build all Docker images from their Dockerfiles.
3. Start all containers in detached mode.

---

## Project structure

```
inception/
├── Makefile
├── .gitignore
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
├── secrets/                        # ← GITIGNORED, create manually
│   ├── admin.txt                   # WordPress admin password
│   ├── credentials.txt             # WordPress user password
│   ├── db_password.txt             # MariaDB user password
│   ├── db_root_password.txt        # MariaDB root password
│   └── ftp_password.txt            # FTP user password
└── srcs/
    ├── docker-compose.yml
    ├── .env                        # Non-sensitive env vars
    └── requirements/
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/nginx.conf
        │   └── tools/generate_ssl.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   ├── conf/www.conf
        │   └── tools/wp_setup.sh
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/my.cnf
        │   ├── conf/init.sql
        │   └── tools/init_db.sh
        ├── redis/
        │   └── Dockerfile
        ├── ftp/
        │   ├── Dockerfile
        │   └── tools/
        │       ├── vsftpd.conf
        │       └── ftp_setup.sh
        ├── static/
        │   ├── Dockerfile
        │   └── index.html
        └── adminer/
            └── Dockerfile
```

---

## Managing containers and volumes

```bash
# Rebuild a single service after changes
docker compose -f srcs/docker-compose.yml build wordpress
docker compose -f srcs/docker-compose.yml up -d wordpress

# Open a shell inside a container
docker exec -it wordpress bash
docker exec -it mariadb bash
docker exec -it nginx bash
docker exec -it redis bash
docker exec -it ftp bash

# Connect to MariaDB directly
docker exec -it mariadb mysql -u wpuser -p wordpress

# Test Redis connection
docker exec -it redis redis-cli ping

# List volumes
docker volume ls

# Inspect a volume
docker volume inspect srcs_wordpress_files
docker volume inspect srcs_db_data
```

---

## Where data is stored and how it persists

| Volume | Host path | Container path |
|--------|-----------|----------------|
| `srcs_wordpress_files` | `/home/alfsanch/data/wordpress` | `/var/www/html` (wordpress, nginx, ftp) |
| `srcs_db_data` | `/home/alfsanch/data/mariadb` | `/var/lib/mysql` |

Data survives `make down` (containers removed) but is deleted by `make fclean`.

---

## How secrets work

Docker secrets are mounted as read-only files at `/run/secrets/<name>` inside the container. Scripts read them with:

```bash
DB_PASSWORD=$(cat /run/secrets/db_password)
```

This way passwords never appear in environment variables, image layers, or `docker inspect` output.

---

## Bonus services

### Redis
Redis runs as an object cache for WordPress. On first boot, `wp_setup.sh` installs and activates the `redis-cache` plugin via WP-CLI, sets `WP_REDIS_HOST=redis` in `wp-config.php`, and enables the object cache. Redis is internal only — not exposed outside the Docker network.

### FTP
The FTP container (`vsftpd`) runs in passive mode on ports 21 and 21100–21110. It creates a system user `ftpuser` whose home directory is the WordPress volume (`/var/www/html`). The FTP password is read from `/run/secrets/ftp_password`. Connect with any FTP client in passive mode.

### Static website
A lightweight nginx container serves the custom `index.html` on port 80. No PHP, no database dependency — purely static.

### Adminer
A single PHP file served by `php -S` on port 8080. Access at `http://alfsanch.42.fr:8080/adminer.php`. Connect with server `mariadb`, user `wpuser`, password from `secrets/db_password.txt`, database `wordpress`.

---

## Useful debugging commands

```bash
# Check nginx config syntax
docker exec nginx nginx -t

# Check php-fpm is listening on 9000
docker exec wordpress ss -tlnp | grep 9000

# Check MariaDB is running
docker exec mariadb mysqladmin -u root -p status

# Check Redis is responding
docker exec redis redis-cli ping

# Check Redis cache status from WordPress
docker exec wordpress wp redis status --allow-root --path=/var/www/html

# Follow logs of a single service
docker logs -f nginx
docker logs -f wordpress
docker logs -f redis
```
