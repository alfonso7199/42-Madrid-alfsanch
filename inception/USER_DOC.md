# USER_DOC — Inception

## What services does this stack provide?

### Mandatory services

| Service | Description | Port |
|---------|-------------|------|
| NGINX | Reverse proxy and HTTPS entry point | 443 |
| WordPress | CMS web application | Internal (9000) |
| MariaDB | Relational database | Internal (3306) |

NGINX is the **only service reachable from outside on port 443** — WordPress and MariaDB are not directly accessible.

### Bonus services

| Service | Description | Port |
|---------|-------------|------|
| Redis | Object cache for WordPress (speeds up page loads) | Internal (6379) |
| FTP | FTP server to access WordPress files | 21 |
| Static website | Custom static HTML site | 80 |
| Adminer | Web interface to inspect and manage the database | 8080 |

## Starting and stopping the project

```bash
# Start everything (builds images if needed)
make

# Stop containers without removing them
make stop

# Start them again
make start

# Stop and remove containers (data is preserved)
make down

# Full reset — removes containers AND all stored data
make fclean && make
```

## Accessing the services

Make sure your `/etc/hosts` has this line first:
```
127.0.0.1  alfsanch.42.fr
```

| Service | URL |
|---------|-----|
| WordPress site | `https://alfsanch.42.fr` |
| WordPress admin | `https://alfsanch.42.fr/wp-admin` |
| Static website | `http://alfsanch.42.fr` (port 80) |
| Adminer | `http://alfsanch.42.fr:8080/adminer.php` |

For WordPress and Adminer: accept the self-signed certificate warning (click *Advanced → Proceed*).

## Accessing the WordPress admin panel

Go to `https://alfsanch.42.fr/wp-admin`

| Field | Value |
|-------|-------|
| Username | `alfsanch_sudo` |
| Password | see `secrets/admin.txt` |

## Accessing Adminer

Go to `http://alfsanch.42.fr:8080/adminer.php`

| Field | Value |
|-------|-------|
| System | MySQL |
| Server | `mariadb` |
| Username | `wpuser` |
| Password | see `secrets/db_password.txt` |
| Database | `wordpress` |

## Accessing via FTP

Connect to `alfsanch.42.fr` on port 21.

| Field | Value |
|-------|-------|
| Username | `ftpuser` |
| Password | see `secrets/ftp_password.txt` |
| Mode | Passive |

The FTP root points directly to the WordPress files volume.

## Where are the credentials stored?

| Credential | File |
|-----------|------|
| WordPress admin password | `secrets/admin.txt` |
| WordPress user password | `secrets/credentials.txt` |
| MariaDB user password | `secrets/db_password.txt` |
| MariaDB root password | `secrets/db_root_password.txt` |
| FTP user password | `secrets/ftp_password.txt` |

> These files are **gitignored** and must never be committed.

## Checking that services are running

```bash
# Status of all containers
make status

# Live logs
make logs

# Check individual container
docker logs nginx
docker logs wordpress
docker logs mariadb
docker logs redis
docker logs ftp
docker logs static
docker logs adminer
```

Expected output of `make status` — all containers should show `Up`:

```
NAME        STATUS    PORTS
nginx       Up        0.0.0.0:443->443/tcp
wordpress   Up        9000/tcp
mariadb     Up        3306/tcp
redis       Up        6379/tcp
ftp         Up        0.0.0.0:21->21/tcp
static      Up        0.0.0.0:80->80/tcp
adminer     Up        0.0.0.0:8080->8080/tcp
```
