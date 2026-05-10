#!/bin/bash
set -e

echo ">>> waiting for mariadb..."
until mysqladmin ping -h"mariadb" -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" --silent 2>/dev/null; do
    sleep 2
done
echo ">>> mariaDB ready"

if [ ! -f /var/www/html/wp-config.php ]; then
    echo ">>> WordPress is being configured..."

    wp config create --allow-root --dbname="${MYSQL_DATABASE}" --dbuser="${MYSQL_USER}" --dbpass="${MYSQL_PASSWORD}" --dbhost=mariadb --path='/var/www/html'
    wp core install --allow-root --url="${DOMAIN_NAME}" --title="Inception" --admin_user="${WP_ADMIN_USER}" --admin_password="${WP_ADMIN_PASS}" --admin_email="${WP_ADMIN_EMAIL}" --path='/var/www/html'
    wp user create --allow-root "${WP_USER}" "${WP_USER_EMAIL}" --role=author --user_pass="${WP_USER_PASS}" --path='/var/www/html'

    echo ">>> WordPress installation completed"
else
    echo ">>> WordPress is already installed. it's being skipped.."
fi

mkdir -p /run/php

echo ">>> PHP-FPM starting..."
exec php-fpm7.4 -F