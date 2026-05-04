#!/bin/bash
set -e

# WordPress'in kurulabilmesi için veritabanının hazır olması şarttır. MariaDB (veritabanı) konteyneri bazen WordPress'ten daha yavaş açılabilir. Bu döngü sürekli veritabanına "Hazır mısın?" diye sorar. MariaDB "Hazırım" yanıtı verene kadar WordPress kurulumunu bekletir (Böylece sistemin çökmesini engeller).
# her 2 saniye de bir MariaDB'ye ping atar ve MariaDB hazır olduğunda döngüden çıkar. 
echo ">>> waiting for mariadb..."
until mysqladmin ping -h"mariadb" -u"${MYSQL_USER}" -p"${MYSQL_PASSWORD}" --silent 2>/dev/null; do
    sleep 2
done
echo ">>> mariaDB ready"

# if: Eğer WordPress (wp-config.php) daha önce kurulmadıysa kurulumu yap
# neden if var: Container restart olursa: tekrar kurulum yapılmasın, veri sıfırlanmasın
if [ ! -f /var/www/html/wp-config.php ]; then
    echo ">>> WordPress is being configured..."

    wp config create --allow-root --dbname="${MYSQL_DATABASE}" --dbuser="${MYSQL_USER}" --dbpass="${MYSQL_PASSWORD}" --dbhost=mariadb --path='/var/www/html'
    wp core install --allow-root --url="${DOMAIN_NAME}" --title="Inception" --admin_user="${WP_ADMIN_USER}" --admin_password="${WP_ADMIN_PASS}" --admin_email="${WP_ADMIN_EMAIL}" --path='/var/www/html'
    wp user create --allow-root "${WP_USER}" "${WP_USER_EMAIL}" --role=author --user_pass="${WP_USER_PASS}" --path='/var/www/html'

    echo ">>> WordPress installation completed"
else
    echo ">>> WordPress is already installed. it's being skipped.."
fi

# php runtime klasörü: php-fpm çalışması için gerekli.
mkdir -p /run/php

echo ">>> PHP-FPM starting..."
exec php-fpm7.4 -F



# Bu script, bir Docker container içinde WordPress kurulumunu otomatikleştiren entrypoint (başlatma) scripti.
# komutlar
## 1. wp config create: WordPress'in wp-config.php dosyasını oluşturur ve veritabanı bağlantı bilgilerini ekler.
## 2. wp core install: WordPress sistemini initialize eder ve temel site bilgilerini (site URL'si, başlık, admin kullanıcı adı ve şifresi) sağlar.
## 3. wp user create: Ek bir WordPress kullanıcısı oluşturur (örneğin, içerik yazarı rolünde).

# Script'in genel akışı:
## 1. Script başlar
## 2. MariaDB beklenir
## 3. WordPress kurulu mu kontrol edilir
## 4. Değilse:
##    - wp-config oluşturulur
##    - core install yapılır
##    - user oluşturulur
## 5. PHP runtime hazırlanır
## 6. PHP-FPM başlatılır