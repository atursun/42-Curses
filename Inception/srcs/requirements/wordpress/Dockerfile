FROM debian:bullseye

RUN apt update && apt install -y php7.4-fpm php7.4-mysql default-mysql-client curl

RUN mkdir -p /var/www/html /run/php

WORKDIR /var/www/html

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

RUN wp core download --allow-root --path=/var/www/html

RUN sed -i 's|listen = /run/php/php7.4-fpm.sock|listen = 9000|g' \
    /etc/php/7.4/fpm/pool.d/www.conf

RUN sed -i 's|^listen.allowed_clients = 127.0.0.1|;listen.allowed_clients = 127.0.0.1|g' \
    /etc/php/7.4/fpm/pool.d/www.conf

RUN chown -R www-data:www-data /var/www/html

COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

EXPOSE 9000

CMD ["/setup.sh"]