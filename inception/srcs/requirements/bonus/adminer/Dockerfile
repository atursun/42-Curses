################################################################################
# 
# Amaç: MariaDB veritabanını web tarayıcısından yönetmek için 
#       kullanıcı dostu bir arayüz sağlamak.
# 
# İçerik: Debian Bullseye tabanlı Adminer (hafif veritabanı yönetim aracı)
# Fonksiyonlar:
#   1. Port 85'te çalışır
#   2. Tarayıcıdan MariaDB'ye bağlanma, tablo görüntüleme, SQL sorgusu çalıştırma
#   3. Nginx tarafından https://domain/adminer'dan erişilir
# 
# Teknik: PHP'nin built-in web sunucusu (php -S) kullanılır.
#         Ayrı bir Nginx/Apache kurmaya gerek yoktur.
################################################################################

FROM debian:bullseye

RUN apt update && apt install -y php php-mysqli wget

WORKDIR /var/www

RUN wget https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php -O index.php

RUN chown -R root:root /var/www/index.php && chmod 755 /var/www/index.php

EXPOSE 85

# Bu çok zekice bir satırdır. Normalde WordPress'te gördüğümüz gibi PHP dosyalarını sunmak için Nginx veya Apache gibi bir sunucuya ihtiyaç vardır. Ancak PHP'nin kendi içinde gömülü, çok hafif bir web sunucusu vardır! (Built-in Web Server).
# Böylece ayrı bir Nginx veya Apache kurmadan;
# php -S komutuyla, 0.0.0.0:85 (tüm ağdan gelenlere 85 portundan cevap ver) diyerek web sunucusunu ayağa kaldırır. -t /var/www ile de ana dizinin (yani index.php'nin bulunduğu klasörün) kendi başlattığı mini sunucunun çalıştığı yer olduğunu belirtir.
CMD ["php", "-S", "0.0.0.0:85", "-t", "/var/www"]