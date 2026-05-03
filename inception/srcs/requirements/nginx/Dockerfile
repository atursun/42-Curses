################################################################################
# 
# Amaç: İnternet'ten gelen HTTPS isteklerini karşılamak ve işlemek
#       (ön kapı/gateway görevini üstlenme).
# 
# İçerik: Debian Bullseye tabanlı Nginx web sunucusu
# Fonksiyonlar:
#   1. HTTPS (SSL/TLS) trafiğini 443 portunda dinler
#   2. Statik dosyaları (CSS, JS, resim) doğrudan sunar
#   3. Dinamik PHP isteklerini wordpress:9000'e (PHP-FPM) yönlendirir
#   4. Bonus hizmetlerine route proxy'si yapar (/adminer, /static-website)
# 
# SSL Sertifikası: Self-signed sertifika otomatik oluşturulur (365 gün geçerli).
#                  atursun.42.fr alan adı için özel olarak üretilir.
################################################################################

FROM debian:bullseye

RUN apt update && apt install -y nginx openssl

# web sitenin güvenli (HTTPS) çalışabilmesi için bir SSL sertifikası oluşturuyor:
# Önce sertifikaların duracağı klasörleri oluşturuyor (mkdir).
# openssl req komutu ile 365 gün geçerli, şifresi olmayan (-nodes) ve 2048 bit şifreleme kullanan self-signed (kendi imzaladığı) bir sertifika yaratıyor.
# Bu sertifika atursun.42.fr alan adı (Common Name) için özel olarak oluşturuluyor (-subj "/CN=atursun.42.fr").
RUN mkdir -p /etc/ssl/certs /etc/ssl/private && \
	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-keyout /etc/ssl/private/key.pem \
	-out /etc/ssl/certs/cert.pem \
	-subj "/CN=atursun.42.fr"

COPY conf/nginx.conf /etc/nginx/nginx.conf

EXPOSE 443

# Konteyner ayağa kalktığında çalışacak olan ana komuttur.
# Nginx'i başlatır. Normalde Nginx işletim sisteminin arka planında (daemon olarak) çalışır.
# Fakat Docker'da (container'da) ana süreç biterse konteyner de kapanır
# Bu yüzden daemon off; parametresi eklenerek Nginx'in arka plana atılması engelleniyor,
# böylece konteynerin sürekli açık kalması sağlanıyor.
CMD ["nginx", "-g", "daemon off;"]