NAME	= inception
COMPOSE	= docker compose -f srcs/docker-compose.yml --env-file srcs/.env


all: up

up: build
	@mkdir -p /home/atursun/data/wordpress /home/atursun/data/mariadb
	@$(COMPOSE) up -d

build:
	@$(COMPOSE) build

down:
	@$(COMPOSE) down

stop:
	@$(COMPOSE) stop

start:
	@$(COMPOSE) up -d

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