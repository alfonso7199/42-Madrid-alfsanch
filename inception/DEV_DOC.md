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
# Secrets — replace each value with your own passwords "your db pass" should be the pass you use to the service
mkdir -p secrets
echo "your_db_password"    > secrets/db_password.txt
echo "your_root_password"  > secrets/db_root_password.txt
echo "your_admin_password" > secrets/admin.txt
echo "your_user_password"  > secrets/credentials.txt
```

### 3. Create the `.env` file

The `.env` is also gitignored. Create it at `srcs/.env`:
Example of .env:

```bash
cat > srcs/.env << 'EOF'
# Domain (must match /etc/hosts entry)
DOMAIN_NAME=alfsanch.42.fr

# MariaDB
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser

# WordPress
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
2. Build the three Docker images from their Dockerfiles.
3. Start all containers in detached mode.

---

## Project structure

```
inception/
├── Makefile                        # Entry point: make / make down / make fclean
├── .gitignore
├── README.md
├── USER_DOC.md
├── DEV_DOC.md
├── secrets/                        # ← GITIGNORED, create manually
│   ├── credentials.txt             # WordPress admin password
│   ├── db_password.txt             # MariaDB user password
│   └── db_root_password.txt        # MariaDB root password
└── srcs/
    ├── docker-compose.yml          # Defines services, volumes, network, secrets
    ├── .env                        # Non-sensitive env vars (domain, db name, usernames)
    └── requirements/
        ├── nginx/
        │   ├── Dockerfile          # FROM debian:bookworm, installs nginx + openssl
        │   ├── conf/nginx.conf     # TLS-only server block, fastcgi_pass to wordpress:9000
        │   └── tools/generate_ssl.sh  # Generates self-signed cert at build time
        ├── wordpress/
        │   ├── Dockerfile          # FROM debian:bookworm, installs php8.2-fpm + wp-cli
        │   ├── conf/www.conf       # php-fpm pool: listen 0.0.0.0:9000
        │   └── tools/wp_setup.sh   # Downloads WP, creates config, installs, starts php-fpm
        └── mariadb/
            ├── Dockerfile          # FROM debian:bookworm, installs mariadb-server
            ├── conf/my.cnf         # bind-address=0.0.0.0, skip-name-resolve
            └── tools/init_db.sh    # Initializes DB + users on first boot, starts mysqld
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

# Connect to MariaDB directly
docker exec -it mariadb mysql -u wpuser -p wordpress

# List volumes
docker volume ls

# Inspect a volume
docker volume inspect inception_wordpress_files
docker volume inspect inception_db_data
```

---

## Where data is stored and how it persists

Both named volumes are backed by directories on the host VM:

| Volume | Host path | Container path |
|--------|-----------|----------------|
| `inception_wordpress_files` | `/home/alfsanch/data/wordpress` | `/var/www/html` |
| `inception_db_data` | `/home/alfsanch/data/mariadb` | `/var/lib/mysql` |

Data survives `make down` (containers removed) but is deleted by `make fclean`.

---

## How secrets work

Docker secrets are mounted as read-only files at `/run/secrets/<name>` inside the container. Scripts read them with:

```bash
DB_PASSWORD=$(cat /run/secrets/db_password)
```

This way passwords never appear in environment variables, image layers, or `docker inspect` output.

---

## Useful debugging commands

```bash
# Check nginx config syntax
docker exec nginx nginx -t

# Check php-fpm is listening on 9000
docker exec wordpress ss -tlnp | grep 9000

# Check MariaDB is running
docker exec mariadb mysqladmin -u root -p status

# Follow logs of a single service
docker logs -f nginx
```
