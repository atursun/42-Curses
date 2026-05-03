################################################################################
# 
# Amaç: Statik HTML içeriği sunmak (resim, CSS, JS gibi dinamik olmayan dosyalar).
# 
# İçerik: Debian Bullseye tabanlı Nginx web sunucusu
# Fonksiyonlar:
#   1. Port 80'de çalışır
#   2. index.html ve diğer statik dosyaları sunar
#   3. Nginx tarafından https://domain/static-website'dan erişilir
# 
# Kullanım: örnek statik sayfa sunma görevini yerine getirir.
################################################################################

FROM debian:bullseye

RUN apt update && apt install -y nginx

COPY tools/index.html /var/www/html/

EXPOSE 80

CMD ["nginx", "-g", "daemon off;"]