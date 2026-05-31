*This project has been created as part of the 42 curriculum by alfsanch*

# Inception

## Description

Inception is a system administration project that consists of building a small web infrastructure using **Docker Compose**. All services run in isolated containers built from scratch — no pre-built images from DockerHub are used (except the base OS).

### Mandatory services

| Service | Description | Port |
|---------|-------------|------|
| **NGINX** | Only entry point, TLSv1.2/TLSv1.3 | 443 |
| **WordPress + php-fpm** | CMS web application | 9000 (internal) |
| **MariaDB** | Relational database | 3306 (internal) |

### Bonus services

| Service | Description | Port |
|---------|-------------|------|
| **Redis** | Object cache for WordPress | 6379 (internal) |
| **FTP** | FTP access to the WordPress volume | 21 |
| **Static website** | Custom static site (HTML/CSS) | 80 |
| **Adminer** | Web-based database manager | 8080 |

Two named Docker volumes persist data across container restarts: one for WordPress files and one for the database. All services communicate over a private Docker network called `inception`.

### Virtual Machines vs Docker

A Virtual Machine emulates an entire OS with its own kernel, consuming gigabytes of RAM and disk. Docker containers share the host kernel and are isolated at the process level using Linux namespaces and cgroups — they are lightweight, start in milliseconds, and are fully reproducible via a Dockerfile.

### Secrets vs Environment Variables

Environment variables (`.env`) are suitable for non-sensitive configuration (domain name, usernames). Secrets (Docker secrets, stored as files in `/run/secrets/`) are the right tool for passwords and credentials because they are mounted in memory only, never written to the image layers, and not visible in `docker inspect`.

### Docker Network vs Host Network

With `network: host` a container shares the host's network stack directly — no isolation, no NAT, ports are exposed as-is. A Docker bridge network (used here) creates an isolated virtual network: containers can talk to each other by service name (DNS), but are not reachable from outside unless a port is explicitly published.

### Docker Volumes vs Bind Mounts

Bind mounts link a host path directly into the container — useful for development but brittle (depends on the host directory existing). Named volumes are managed by Docker, stored under `/var/lib/docker/volumes/` by default, and are portable. This project uses named volumes with a `bind` driver option so data lands at `/home/alfsanch/data/` on the host VM.

## Instructions

### Prerequisites

- Docker and Docker Compose installed on a Linux VM.
- Add the domain to `/etc/hosts` on the VM:
  ```
  127.0.0.1  alfsanch.42.fr
  ```

### Clone and run

```bash
git clone https://github.com/alfonso7199/42-Madrid-alfsanch.git
cd 42-Madrid-alfsanch/inception
make
```

`make` will create the data directories, build all images and start the containers.

### Other Makefile targets

| Command | Action |
|---------|--------|
| `make up` | Build and start all containers |
| `make down` | Stop and remove containers |
| `make stop` | Stop containers (keep them) |
| `make start` | Restart stopped containers |
| `make logs` | Follow logs of all services |
| `make status` | Show container status |
| `make clean` | Stop containers and prune images |
| `make fclean` | Full reset including data volumes |
| `make re` | Full rebuild from scratch |

### Access

| URL | Service |
|-----|---------|
| `https://alfsanch.42.fr` | WordPress site |
| `https://alfsanch.42.fr/wp-admin` | WordPress admin panel |
| `http://alfsanch.42.fr:80` | Static website |
| `http://alfsanch.42.fr:8080/adminer.php` | Adminer (DB manager) |
| FTP: `alfsanch.42.fr:21` | FTP access to WordPress files |

## Resources

- [Docker documentation](https://docs.docker.com/)
- [Docker Compose reference](https://docs.docker.com/compose/compose-file/)
- [Dockerfile best practices](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
- [WP-CLI documentation](https://wp-cli.org/)
- [NGINX beginner's guide](https://nginx.org/en/docs/beginners_guide.html)
- [MariaDB documentation](https://mariadb.com/kb/en/documentation/)
- [php-fpm configuration](https://www.php.net/manual/en/install.fpm.configuration.php)
- [Redis documentation](https://redis.io/docs/)
- [Redis Object Cache plugin](https://wordpress.org/plugins/redis-cache/)
- [vsftpd documentation](https://security.appspot.com/vsftpd.html)
- [Adminer documentation](https://www.adminer.org/)
- [RFC — TLS 1.2](https://datatracker.ietf.org/doc/html/rfc5246) / [TLS 1.3](https://datatracker.ietf.org/doc/html/rfc8446)

### AI usage

AI was used to accelerate the scaffolding of boilerplate configuration files (nginx.conf, www.conf, docker-compose.yml structure, vsftpd.conf) and to cross-check Dockerfile best practices. All generated content was reviewed, understood, and adapted to the specific requirements of the project. The logic of init scripts, secret handling, Redis cache integration and the overall architecture were designed and validated manually.
