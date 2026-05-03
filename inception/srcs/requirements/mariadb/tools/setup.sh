#!/bin/sh
set -e

# Soket ve veri dizinlerini sağlama al
mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld
chown -R mysql:mysql /var/lib/mysql

# 1. Veri dizini boşsa initialize et
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo ">>> MariaDB data dizini initialize ediliyor..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db > /dev/null
fi

# 2. SQL komutlarını geçici bir dosyaya hazırla
tempfile=$(mktemp)
cat << SQL > "$tempfile"
USE mysql;
FLUSH PRIVILEGES;
-- Eski root ve gereksiz kullanıcıları temizle
DELETE FROM mysql.user WHERE User='';
DROP DATABASE IF EXISTS test;
-- Şifreleme ve Yetkilendirme
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
SQL

# 3. MariaDB'yi bootstrap modunda çalıştır (SQL dosyasını içeri aktarır ve kapanır)
echo ">>> Konfigürasyon uygulanıyor..."
mysqld --user=mysql --bootstrap < "$tempfile"
rm -f "$tempfile"

# 4. MariaDB'yi normal modda başlat
echo ">>> MariaDB hazır ve başlatılıyor..."
exec mysqld --user=mysql --bind-address=0.0.0.0 --port=3306


# -----------------eskisi----------------------
# #!/bin/bash
# set -e

# echo ">>> MariaDB hazırlanıyor..."

# if [ ! -d "/var/lib/mysql/mysql" ]; then
#     echo ">>> MariaDB data dizini initialize ediliyor..."
#     mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null
# fi

# echo ">>> MariaDB geçici modda başlatılıyor (bootstrap)..."
# mysqld --user=mysql --skip-networking --socket=/run/mysqld/mysqld.sock &
# pid="$!"

# echo ">>> MariaDB hazır olana kadar bekleniyor..."
# until mysqladmin ping --socket=/run/mysqld/mysqld.sock --silent 2>/dev/null; do
#     sleep 1
# done

# echo ">>> Kullanıcılar ve yetkiler ayarlanıyor..."
# mysql --protocol=socket -uroot --socket=/run/mysqld/mysqld.sock <<EOF                                                                                                
# ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';                                                                                                
# CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;                                                                                                                 
# CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
# GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';                                                                                              
# FLUSH PRIVILEGES;                                                                                                                                                    
# EOF

# echo ">>> Geçici MariaDB kapatılıyor..."
# mysqladmin --protocol=socket -u root -p"${MYSQL_ROOT_PASSWORD}" --socket=/run/mysqld/mysqld.sock shutdown
# wait "$pid" || true

# echo ">>> MariaDB normal modda başlatılıyor..."
# exec mysqld --user=mysql --bind-address=0.0.0.0 --port=3306



# Özetle, eski kodun ile yeni **Bootstrap** yöntemi arasındaki temel farklar şunlardır:

# ### 1. Çalışma Mantığı (Canlı Müdahale vs. Hazırlık)
# *   **Eski Kod:** MariaDB'yi arka planda başlatıp (`&`), o çalışırken dışarıdan komut göndermeye çalışıyordu. Bu durum, MariaDB tam açılmadan komut gitmesi durumunda bağlantı hatalarına (502'ye yol açan çökmelere) neden oluyordu.
# *   **Yeni Kod (Bootstrap):** MariaDB'yi "sessiz modda" açar. Hiçbir ağ bağlantısı kabul etmeden önce tüm SQL komutlarını (şifre, yetki, database) doğrudan dosya sistemine işler ve kapanır. İşlem bittikten sonra tertemiz bir başlangıç yapar.

# ### 2. Yetkilendirme Gücü
# *   **Eski Kod:** Root şifresini değiştirirken bazen "Access Denied" (Erişim Engellendi) hatasına takılabiliyordu çünkü canlı sistemde şifre değiştirmek için önce sisteme girebilmek gerekir.
# *   **Yeni Kod:** Bootstrap modunda şifre kontrolü devre dışıdır. MariaDB henüz "kapılarını açmadığı" için verdiğin tüm yetki ve şifre komutlarını doğrudan veritabanı çekirdeğine enjekte eder.

# ### 3. Stabilite ve Hız
# *   **Eski Kod:** MariaDB'nin hazır olmasını beklemek (`until mysqladmin ping`), sonra yetkileri vermek ve ardından güvenli şekilde kapatmak için `wait` komutunu kullanıyordu. Bu süreç yavaştı ve takılmalara müsaitti.
# *   **Yeni Kod:** Tüm SQL komutlarını tek bir paket halinde içeri aktarır. Gereksiz beklemeleri ortadan kaldırır. Konteyner ayağa kalktığında veritabanı çoktan yapılandırılmış ve WordPress'ten gelecek bağlantılara hazır hale gelmiş olur.

# **Kısacası:** Yeni yöntem, MariaDB'yi dış dünyaya açmadan önce tüm ayarlarını "mutfakta" bitirip, sofrayı (bağlantıyı) öyle kuruyor. Bu da WordPress'in kapıdan dönmesini ve dolayısıyla senin 502 hatası almanı engelliyor.


# -----------------------------------
# Sistem ve Yazılımda Bootstrap (Önyükleme)

# Bilgisayar veya bir yazılımın, kendi kendini çalıştırabilir hale gelmesi sürecidir.

#     Mantığı: Bir sistemin (örneğin işletim sistemi), en temel seviyedeki küçük bir kod parçasını çalıştırarak daha büyük ve karmaşık olan ana sistemi ayağa kaldırmasıdır.

#     Örnek: Az önceki MariaDB örneğinde kullandığımız --bootstrap modu, veritabanının tüm özellikleri (ağ bağlantısı, kullanıcı yönetimi vb.) açılmadan önce, temel ayarların ve tabloların "sessizce" hazırlanması aşamasını ifade eder.
