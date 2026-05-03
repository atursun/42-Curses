# DEV_DOC - Developer Documentation

This document explains how a developer can set up, build, run, and maintain this project from scratch.

## 1) Environment Setup from Scratch

### Prerequisites

- Docker installed
- Docker Compose installed
- Make installed
- Local domain mapping configured (example):
  - `127.0.0.1 atursun.42.fr`

### Required configuration files

- `srcs/docker-compose.yml`
- `srcs/.env`
- `Makefile`

### Secrets and configuration

Current setup uses environment variables in `srcs/.env` for:
- database credentials
- WordPress admin/user credentials
- domain/login values

For production hardening, prefer dedicated secret handling over plain env files.

## 2) Build and Launch with Makefile and Docker Compose

### Primary commands

- `make` / `make up`  
  Build images and start containers.

- `make build`  
  Build/rebuild images only.

- `make down`  
  Stop and remove the running stack.

- `make restart`  
  Restart stack (`down` + `up`).

- `make re`  
  Full rebuild workflow.

### Direct compose form used by Makefile

`docker compose -f srcs/docker-compose.yml --env-file srcs/.env <command>`

This ensures compose always uses the correct file and env context.

## 3) Manage Containers and Volumes

### Useful container commands

- Service status:  
  `docker compose -f srcs/docker-compose.yml --env-file srcs/.env ps`

- Logs:  
  `docker compose -f srcs/docker-compose.yml --env-file srcs/.env logs`

- Per-service logs:  
  `docker compose -f srcs/docker-compose.yml --env-file srcs/.env logs nginx`

- Exec into container:  
  `docker compose -f srcs/docker-compose.yml --env-file srcs/.env exec wordpress sh`

### Useful volume commands

- List volumes:  
  `docker volume ls`

- Inspect a volume:  
  `docker volume inspect <volume_name>`

- Remove unused volumes carefully:  
  `docker volume prune`

## 4) Data Location and Persistence

### Persistent Docker volumes in this project

- `wordpress` -> mounted at `/var/www/html`
- `mariadb` -> mounted at `/var/lib/mysql`
- `uptime` -> mounted at `/app/data`

These named volumes persist data across container recreation.

### Host-side data path created by Makefile

The Makefile creates:
- `/home/<LOGIN>/data/wordpress`
- `/home/<LOGIN>/data/mariadb`

where `<LOGIN>` is parsed from `srcs/.env`.

## 5) Implementation Notes by Service

### `nginx`
- Public HTTPS entrypoint (`443`)
- Forwards PHP requests to `wordpress:9000`
- Handles bonus route proxies (`/adminer`, `/static-website`)

### `wordpress`
- php-fpm runs on port `9000`
- Startup script waits for MariaDB readiness
- Initializes WordPress via WP-CLI (idempotent behavior via config file check)

### `mariadb`
- Initializes DB/user/grants during setup script
- Runs as foreground process
- Accepts internal network connections

## 6) Quick Developer Validation

- `make up`
- Check status with `make ps`
- Verify URLs:
  - `https://atursun.42.fr`
  - `https://atursun.42.fr/wp-admin`
  - `https://atursun.42.fr/adminer`
- Inspect logs with `make logs`

## 7) Troubleshooting

- `502 Bad Gateway`
  - Verify `wordpress` is running and listening on `9000`.

- WordPress cannot connect to DB
  - Re-check `MYSQL_*` values in `srcs/.env`.
  - Check MariaDB logs.

- Credentials not accepted
  - Confirm `WP_ADMIN_*` / `WP_USER_*` values and startup sequence.

- Data unexpectedly missing
  - Check whether volumes were removed during cleanup.