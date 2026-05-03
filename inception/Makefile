NAME		= inception
COMPOSE		= srcs/docker-compose.yml
ENV_FILE	= srcs/.env
DATA_PATH	= /home/alfsanch/data
SECRETS_DIR	= ./secrets
SECRETS_FILES	= db_password.txt db_root_password.txt admin.txt credentials.txt

# ─────────────────────────────────────────────────────────────────────────────
#  Default target
# ─────────────────────────────────────────────────────────────────────────────

all: up

# ─────────────────────────────────────────────────────────────────────────────
#  Core targets
# ─────────────────────────────────────────────────────────────────────────────

## up       : Build images (if needed) and start all containers in detached mode
up: precheck set-host
	@mkdir -p $(DATA_PATH)/wordpress $(DATA_PATH)/mariadb
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) up -d --build
	@docker ps -a

## build    : Force rebuild all images from scratch (no cache)
build: precheck
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) build --no-cache

## down     : Stop and remove all containers, networks and orphans
down:
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) down --remove-orphans

## stop     : Stop running containers without removing them
stop:
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) stop

## start    : Start previously stopped containers
start:
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) start

## restart  : down + up
restart: down up

# ─────────────────────────────────────────────────────────────────────────────
#  Observability
# ─────────────────────────────────────────────────────────────────────────────

## logs     : Follow live logs of all running containers (Ctrl+C to exit)
logs:
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) logs -f --tail=100

## status   : Show current status of containers, volumes and networks
status:
	@docker compose -f $(COMPOSE) --env-file $(ENV_FILE) ps
	@docker volume ls
	@docker network ls

## debug    : up + logs
debug: up logs

# ─────────────────────────────────────────────────────────────────────────────
#  Cleanup
# ─────────────────────────────────────────────────────────────────────────────

## clean    : down + remove all built images
clean: down
	@docker system prune -af

## fclean   : clean + remove persistent data from host + unset /etc/hosts entry
fclean: unset-host clean
	@if [ -d $(DATA_PATH) ]; then \
		echo "Removing data directory $(DATA_PATH) ..."; \
		sudo rm -rf $(DATA_PATH); \
		echo "Done."; \
	fi
	@docker volume prune -f
	@docker network prune -f
	@docker builder prune -f

## re       : fclean + up
re: fclean up

# ─────────────────────────────────────────────────────────────────────────────
#  Host management
# ─────────────────────────────────────────────────────────────────────────────

# Reads DOMAIN_NAME from .env and adds it to /etc/hosts if not already present
set-host:
	@if [ -f $(ENV_FILE) ]; then \
		DOMAIN=$$(grep '^DOMAIN_NAME=' $(ENV_FILE) | cut -d= -f2); \
		if [ -n "$$DOMAIN" ] && ! grep -q "$$DOMAIN" /etc/hosts; then \
			echo "Adding $$DOMAIN to /etc/hosts ..."; \
			sudo sh -c "echo '127.0.0.1 $$DOMAIN' >> /etc/hosts"; \
			echo "Done."; \
		fi; \
	fi

# Removes the project domain from /etc/hosts
unset-host:
	@if [ -f $(ENV_FILE) ]; then \
		DOMAIN=$$(grep '^DOMAIN_NAME=' $(ENV_FILE) | cut -d= -f2); \
		if [ -n "$$DOMAIN" ] && grep -q "$$DOMAIN" /etc/hosts; then \
			echo "Removing $$DOMAIN from /etc/hosts ..."; \
			sudo sed -i "/$$DOMAIN/d" /etc/hosts; \
			echo "Done."; \
		fi; \
	fi

# ─────────────────────────────────────────────────────────────────────────────
#  Prechecks (run before up/build)
# ─────────────────────────────────────────────────────────────────────────────

# Validate that docker is accessible without sudo
precheck_docker:
	@docker ps >/dev/null 2>&1 || { \
		echo "Error: Docker is not accessible. Add your user to the docker group:"; \
		echo "       sudo usermod -aG docker $$USER && newgrp docker"; \
		exit 1; \
	}

# Validate that the .env file exists
precheck_env:
	@if [ ! -f $(ENV_FILE) ]; then \
		echo "Error: $(ENV_FILE) not found. Create it before running make."; \
		echo "       See DEV_DOC.md for the required contents."; \
		exit 1; \
	fi

# Validate that all secrets files exist and are non-empty
precheck_secrets:
	@missing=0; \
	for f in $(SECRETS_FILES); do \
		if [ ! -s "$(SECRETS_DIR)/$$f" ]; then \
			echo "Error: Secret missing or empty: $(SECRETS_DIR)/$$f"; \
			missing=1; \
		fi; \
	done; \
	[ $$missing -eq 0 ]

precheck: precheck_docker precheck_env precheck_secrets

# ─────────────────────────────────────────────────────────────────────────────
#  Help
# ─────────────────────────────────────────────────────────────────────────────

## help     : Display this help message
help:
	@echo ""
	@echo "  Inception — Makefile reference"
	@echo "  ════════════════════════════════════════════════════════"
	@echo ""
	@echo "  Core"
	@echo "  ────────────────────────────────────────────────────────"
	@echo "  all            Build images (if needed) and start all containers"
	@echo "  up             Same as all"
	@echo "  build          Force rebuild all images from scratch (no cache)"
	@echo "  down           Stop and remove containers, networks and orphans"
	@echo "  stop           Stop containers without removing them"
	@echo "  start          Restart previously stopped containers"
	@echo "  restart        down + up"
	@echo ""
	@echo "  Observability"
	@echo "  ────────────────────────────────────────────────────────"
	@echo "  logs           Follow live logs of all containers"
	@echo "  status         Show status of containers, volumes and networks"
	@echo "  debug          up + logs"
	@echo ""
	@echo "  Cleanup"
	@echo "  ────────────────────────────────────────────────────────"
	@echo "  clean          down + remove all built images"
	@echo "  fclean         clean + remove persistent data (requires sudo)"
	@echo "  re             fclean + up"
	@echo ""
	@echo "  ════════════════════════════════════════════════════════"
	@echo "  Compose file : $(COMPOSE)"
	@echo "  Data path    : $(DATA_PATH)"
	@echo "  Secrets dir  : $(SECRETS_DIR)"
	@echo ""

# ─────────────────────────────────────────────────────────────────────────────

.PHONY: all up build down stop start restart logs status debug \
	clean fclean re set-host unset-host \
	precheck precheck_docker precheck_env precheck_secrets help
