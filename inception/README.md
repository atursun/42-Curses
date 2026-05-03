*This project has been created as part of the 42 curriculum by atursun.*

# Inception

## Description

`Inception` aims to build and manage a multi-service system using Docker, ensuring that all services run together seamlessly.
It provides a secure WordPress setup with:
- `nginx` (TLS entrypoint, reverse proxy)
- `wordpress` + `p>hp-fpm` (application layer)
- `mariadb` (database layer)

The goal is to design a realistic, modular, and persistent web infrastructure where each service runs in its own container, communicates over a dedicated Docker network, and keeps data across restarts via volumes.

### Project Purpose (Core Architecture)

The project is built around three core services:
1. `NGINX` — single public entrypoint (`443`, TLS)
2. `WordPress + php-fpm` — web application layer
3. `MariaDB` — database layer

These services are connected through a dedicated Docker network.  
To prevent data loss, the stack uses two main named volumes:
- one for WordPress files
- one for MariaDB data

Request flow:

`User -> NGINX (443) -> WordPress -> MariaDB`

## Project Description: Docker Usage, Sources, and Design Choices

### Why Docker in this project

Docker is used to package each service with its dependencies, isolate runtime behavior, and make deployment reproducible.  
`docker-compose.yml` orchestrates multi-container communication, startup order, networks, and volumes in one declarative file.

### Sources included in the project

Main implementation sources:
- `srcs/docker-compose.yml`
- `srcs/.env` (local configuration values)
- `srcs/requirements/nginx/*`
- `srcs/requirements/wordpress/*`
- `srcs/requirements/mariadb/*`
- `Makefile`

### Main design choices

- Strict service separation (`nginx`, `wordpress`, `mariadb`)
- Single public entrypoint (`443` on `nginx`)
- Internal-only service communication (`expose` + private bridge network)
- Named volumes for persistent state
- Startup scripts for idempotent initialization (especially DB and WP setup)
- Environment-driven configuration through `.env`

### Required comparisons

#### 1) Virtual Machines vs Docker

- **Virtual Machines** virtualize hardware and run full guest OS instances; they are heavier and slower to boot.
- **Docker containers** virtualize at OS level, sharing the host kernel; they are lighter and faster.
- In this project, Docker is preferred for fast iteration, service isolation, and reproducible builds.

#### 2) Secrets vs Environment Variables

- **Environment variables** are easy to inject and are used in this project for setup automation.
- **Secrets** are safer for sensitive production credentials because they reduce accidental exposure in logs/env dumps.
- For this educational setup, `.env` is used; for production, Docker secrets (or an external secret manager) should be preferred.

#### 3) Docker Network vs Host Network

- **Docker bridge network** isolates containers and allows controlled inter-service communication via service names.
- **Host network** removes this isolation and shares the host network namespace directly.
- This project uses a dedicated bridge network to keep internal services private and reduce attack surface.

#### 4) Docker Volumes vs Bind Mounts

- **Named volumes** are managed by Docker and are best for persistent application data.
- **Bind mounts** map host paths directly and are convenient for development but more coupled to host structure/permissions.
- This project uses named volumes for stable persistence of WordPress and MariaDB data.

## Instructions

### Prerequisites

- Docker installed
- Docker Compose installed
- Local hosts mapping configured (example):
  - `127.0.0.1 atursun.42.fr`
- `srcs/.env` configured for your environment

### Build and execution

From repository root:

- `make` or `make up` -> build and start stack
- `make build` -> build images
- `make down` -> stop stack
- `make restart` -> restart stack
- `make logs` -> show logs
- `make ps` -> show running services
- `make re` -> full rebuild

### Basic usage

- WordPress: `https://atursun.42.fr`
- WordPress admin: `https://atursun.42.fr/wp-admin`

## Additional Information

For detailed usage and operations:
- User guide: `USER_DOC.md`
- Developer guide: `DEV_DOC.md`

## Resources

### Topic references

- Docker / Container
  - [docker](./docs/docker.md)
  - [what is docker ?](https://youtu.be/4XVfmGE1F_w?si=jmS6GlJLjdAajSWR)
  - [docker-github](https://github.com/gkandemi/docker)
  - [docker-setup-and-basic-commands](https://medium.com/@ozelfaruk/docker-kurulumu-ve-temel-komutlar-367d46a07bed)
- [Services (nginx, mariadb..)](./docs/services.md)


### AI usage

AI was **not** used to blindly generate runtime configuration without review.  
All final content and technical alignment were manually checked against the current repository files and subject constraints.