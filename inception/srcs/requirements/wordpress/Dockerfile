################################################################################
# 
# Amaç: PHP-FPM sunucusu ve WordPress uygulama katmanını sağlamak.
# 
# İçerik: Debian Bullseye tabanlı PHP-FPM 7.4 ve WordPress CMS
# Fonksiyonlar:
#   1. PHP-FPM: Port 9000'de çalışır, Nginx'ten gelen PHP isteklerini işler
#   2. WP-CLI: WordPress'i komut satırından kurmak ve yönetmek için kullanılır
#   3. WordPress core: İndirilerek /var/www/html içine yerleştirilir
#   4. Database bağlantısı: MariaDB'ye bağlanır (wp-config.php ile otomatik yapılandırılır)
# 
# Başlangıç: setup.sh script'i WordPress'i tamamen kurar ve yapılandırır (idempotent).
# Veri Kalıcılığı: /var/www/html dizini Docker volume ile host'ta saklanır.
################################################################################

FROM debian:bullseye

RUN apt update && apt install -y \
    php7.4-fpm \
    php7.4-mysql \
    unzip \
    curl \
    wget \
    default-mysql-client

RUN mkdir -p /var/www/html /run/php

WORKDIR /var/www/html

# WP-CLI indir ve kur
# WordPress'i tarayıcıya (arayüze) ihtiyaç duymadan, direkt komut satırından (terminalden) kurmamızı ve yönetmemizi sağlar.
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# WordPress dosyalarını indir
RUN wp core download --allow-root --path=/var/www/html

# PHP-FPM'i 9000 portuna ayarla (socket yerine TCP)
RUN sed -i 's|listen = /run/php/php7.4-fpm.sock|listen = 9000|g' \
    /etc/php/7.4/fpm/pool.d/www.conf

# NGINX başka container'dan bağlanacağı için (TCP) allowed_clients kısıtını kaldır
# Normalde PHP kendi içinde bir dosya üzerinden haberleşir (socket). Ancak bizim mimarimizde Nginx ayrı bir konteynerde olduğu için, PHP'nin dışarıdan gelen bağlantıları dinlemesi gerekir. sed komutlarıyla PHP'nin 9000 portunu dinlemesi sağlanır ve IP kısıtlamaları kaldırılır.
RUN sed -i 's|^listen.allowed_clients = 127.0.0.1|;listen.allowed_clients = 127.0.0.1|g' \
    /etc/php/7.4/fpm/pool.d/www.conf

# www-data kullanıcısının /var/www/html'e yazmasına izin ver
RUN chown -R www-data:www-data /var/www/html

COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

EXPOSE 9000

CMD ["/setup.sh"]