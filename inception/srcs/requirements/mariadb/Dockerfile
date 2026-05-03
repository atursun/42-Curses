################################################################################
# 
# Amaç: WordPress'in verileri (yazılar, sayfalar, kullanıcılar, ayarlar vb.) 
#       depoladığı veritabanı hizmetini sağlamak.
# 
# İçerik: Debian Bullseye tabanlı MariaDB sunucusu
# Fonksiyon: Port 3306 üzerinden internal ağdan veritabanı bağlantıları kabul eder.
#           Startup script (setup.sh) ile MySQL veritabanı, kullanıcı ve izinleri 
#           otomatik olarak yapılandırılır.
# 
# Veri Kalıcılığı: /var/lib/mysql dizini Docker volume ile host'ta saklanır.
################################################################################

FROM debian:bullseye

RUN apt update && apt install -y mariadb-server

RUN mkdir -p /run/mysqld && chown -R mysql:mysql /run/mysqld \
    && chown -R mysql:mysql /var/lib/mysql

COPY tools/setup.sh /setup.sh

RUN chmod +x /setup.sh

EXPOSE 3306

CMD ["/setup.sh"]