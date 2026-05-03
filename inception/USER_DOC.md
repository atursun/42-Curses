# USER_DOC - User Documentation

This file explains how an end user or administrator can operate the Inception stack in simple terms.

## 1) Services Provided by the Stack

Mandatory services:
- `nginx` (public HTTPS entrypoint)
- `wordpress` (website + admin panel)
- `mariadb` (database backend)

Bonus services in this repository:
- `adminer` (database web UI)
- `static-website` (static content route)
- `uptime` (service monitoring dashboard)

## 2) Start and Stop the Project

From repository root:

- Start/build:
  - `make` or `make up`
- Stop:
  - `make down`
- Restart:
  - `make restart`
- Rebuild from scratch:
  - `make re`

Useful runtime commands:
- Show service status: `make ps`
- Show logs: `make logs`

## 3) Access the Website and Admin Panel

Make sure your hosts file maps the domain (example):
- `127.0.0.1 atursun.42.fr`

Then access:
- Website: `https://atursun.42.fr`
- WordPress admin panel: `https://atursun.42.fr/wp-admin`
- Adminer: `https://atursun.42.fr/adminer`
- Static website: `https://atursun.42.fr/static-website`
- Uptime dashboard: `http://atursun.42.fr:3001`

Note: the TLS certificate is self-signed in this setup, so browser warnings are expected.

## 4) Locate and Manage Credentials

Credentials are configured in:
- `srcs/.env`

Important values:
- WordPress admin: `WP_ADMIN_USER`, `WP_ADMIN_PASS`, `WP_ADMIN_EMAIL`
- WordPress user: `WP_USER`, `WP_USER_PASS`, `WP_USER_EMAIL`
- MariaDB: `MYSQL_DATABASE`, `MYSQL_USER`, `MYSQL_PASSWORD`, `MYSQL_ROOT_PASSWORD`

Adminer login tips:
- System: `MySQL`
- Server: `mariadb`
- Username/password: values from `.env`

Security note:
- Keep `.env` private.
- Rotate passwords if credentials were shared by mistake.

## 5) Check That Services Are Running Correctly

### Fast checks

- `make ps` -> all required containers should be `Up`
- `make logs` -> no repeated fatal errors

### Functional checks

- Open website URL and verify homepage loads
- Log in to `/wp-admin`
- Open `/adminer` and verify DB connection
- Open Uptime dashboard and confirm service states

### If something fails

- Run `make logs` and inspect failing service messages
- Restart stack with `make restart`
- Rebuild with `make re` if needed

## 6) Common Problems

- `502 Bad Gateway`
  - Usually WordPress/php-fpm is not reachable from NGINX.
- WordPress login fails
  - Re-check `WP_ADMIN_*` values in `.env`.
- Adminer cannot connect
  - Use `mariadb` as server host, not `localhost`.
- Domain does not open
  - Verify hosts file mapping and HTTPS URL.