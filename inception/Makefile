NAME        := inception
SRC_DIR     := srcs
COMPOSE_FILE:= $(SRC_DIR)/docker-compose.yml
ENV_FILE    := $(SRC_DIR)/.env

LOGIN       := $(shell sed -n 's/^LOGIN=//p' $(ENV_FILE))
DATA_DIR    := /home/$(LOGIN)/data
WP_DATA     := $(DATA_DIR)/wordpress
DB_DATA     := $(DATA_DIR)/mariadb

COMPOSE     := docker compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE)


all: up

up: build
	@mkdir -p $(WP_DATA) $(DB_DATA)
	@$(COMPOSE) up -d

build:
	@$(COMPOSE) build

down:
	@$(COMPOSE) down

stop:
	@$(COMPOSE) stop

start:
	@$(COMPOSE) start

restart: down up

logs:
	@$(COMPOSE) logs

ps:
	@$(COMPOSE) ps

clean: down
	@$(COMPOSE) down -v

fclean: down
	@$(COMPOSE) down -v --rmi all
	@docker system prune -f

re: fclean up

.PHONY: all up build down stop start restart logs ps clean fclean re