# USER_DOC — Inception

## What services does this stack provide?

| Service | Description | Port |
|---------|-------------|------|
| NGINX | Reverse proxy and HTTPS entry point | 443 |
| WordPress | CMS web application | Internal (9000) |
| MariaDB | Relational database | Internal (3306) |

NGINX is the **only service reachable from outside** — WordPress and MariaDB are not directly accessible.

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

## Accessing the website

1. Make sure your `/etc/hosts` has this line:
   ```
   127.0.0.1  alfsanch.42.fr
   ```
2. Open a browser and go to `https://alfsanch.42.fr`
3. Accept the self-signed certificate warning (click *Advanced → Proceed*).

## Accessing the WordPress admin panel

Go to `https://alfsanch.42.fr/wp-admin`

| Field | Value |
|-------|-------|
| Username | `alfsanch_admin` |
| Password | see `secrets/credentials.txt` |

## Where are the credentials stored?

| Credential | File |
|-----------|------|
| WordPress admin password | `secrets/credentials.txt` |
| MariaDB user password | `secrets/db_password.txt` |
| MariaDB root password | `secrets/db_root_password.txt` |

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
```

Expected output of `make status` — all three containers should show `Up`:

```
NAME        STATUS    PORTS
nginx       Up        0.0.0.0:443->443/tcp
wordpress   Up        9000/tcp
mariadb     Up        3306/tcp
```
