#!/bin/sh
set -e

# MariaDB’nin çalışacağı klasörleri oluşturuyor
# İzinleri mysql kullanıcısına veriyor
mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld    # socket dosyası
chown -R mysql:mysql /var/lib/mysql # database dosyaları

# “Eğer database daha önce oluşturulmadıysa kur”
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo ">>> Initializing the MariaDB data directory..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db > /dev/null
fi

# 2. SQL komutlarını geçici bir dosyaya hazırla (Geçici bir SQL dosyası oluşturuluyor) sistem temizliği, (boş kullanıcıları siler, test DB’yi kaldırır)
tempfile=$(mktemp)
cat << SQL > "$tempfile"
USE mysql;
FLUSH PRIVILEGES;
DELETE FROM mysql.user WHERE User='';
DROP DATABASE IF EXISTS test;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`; 
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
SQL

# MariaDB'yi bootstrap modunda çalıştır (SQL dosyasını içeri aktarır ve kapanır)
# MariaDB’yi “normal server gibi değil, sadece SQL çalıştıran modda açmak”
echo ">>> Configuration is being applied..."
mysqld --user=mysql --bootstrap < "$tempfile"
rm -f "$tempfile"   # geçici SQL dosyası silinir

# 4. MariaDB'yi normal modda başlat
echo ">>> MariaDB is ready and starting..."
exec mysqld --user=mysql --bind-address=0.0.0.0 --port=3306



# Bu script, bir Docker container içinde MariaDB sunucusunu ilk kez initialize eden ve güvenli şekilde başlatan entrypoint scriptidir.
# genel akış
# # 1. Dosya izinleri hazırlanır
# # 2. DB yoksa initialize edilir
# # 3. SQL ile kullanıcı + DB oluşturulur
# # 4. bootstrap mode ile setup yapılır
# # 5. mysqld normal modda başlatılır


# tempfile, MariaDB’nin bootstrap modunda çalıştıracağı SQL komutlarını güvenli, stabil ve dosya tabanlı şekilde iletmek için kullanılır.
# Bootstrap mode, MariaDB’nin ilk kurulum sırasında sistem tablolarını, kullanıcıları ve veritabanlarını oluşturmak için SQL komutlarını client bağlantısı olmadan doğrudan çalıştırdığı özel başlatma modudur.
