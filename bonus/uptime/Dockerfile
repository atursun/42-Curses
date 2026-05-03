################################################################################
# 
# Amaç: Tüm hizmetlerin/servislerin çalışıp çalışmadığını izlemek ve sistem sağlığını görselleştirmek.
#
# İçerik: Debian Bullseye tabanlı Uptime Kuma (açık kaynaklı izleme aracı)
# Fonksiyonlar:
#   1. Port 3001'de çalışır
#   2. Web tabanlı gösterge paneli (dashboard) sunar
#   3. Nginx, WordPress, Adminer vb. hizmetlerin durumunu izler
#   4. Nginx tarafından http://domain:3001 üzerinden erişilir
# 
# Teknoloji: Node.js + Express tabanlı, hafif ve hızlı izleme sistemi.
################################################################################

FROM debian:bullseye

RUN apt update && apt install -y curl git \
    && curl -fsSL https://deb.nodesource.com/setup_18.x | bash - \
    && apt install -y nodejs \
    && git clone https://github.com/louislam/uptime-kuma.git /app \
    && cd /app \
    && npm run setup

WORKDIR /app

EXPOSE 3001

CMD ["node", "server/server.js"]


# # 1. Gerekli araçları yükle
# apt update && apt install -y curl git
#   ↓
#   Sistem paketlerini güncelle ve:
#   - curl = internetten dosya/veri indirmek için
#   - git = GitHub'dan kod klonlamak için

# # 2. Node.js 18 deposunu ekle
# && curl -fsSL https://deb.nodesource.com/setup_18.x | bash -
#   ↓
#   NodeSource'dan setup scripti indir ve çalıştır
#   (Resmi Node.js deposu eklenir - debian paketinde yüksek sürüm yoktur)

# # 3. Node.js'i yükle
# && apt install -y nodejs
#   ↓
#   Node.js ve npm (paket yöneticisi) yükle

# # 4. Uptime Kuma kaynak kodunu indir
# && git clone https://github.com/louislam/uptime-kuma.git /app
#   ↓
#   GitHub'dan tüm kaynak kodları /app dizinine kopyala

# # 5. Uptime Kuma dizinine gir
# && cd /app
#   ↓
#   Çalışma dizinini /app'e değiştir

# # 6. Uptime Kuma'nın bağımlılıklarını kur
# && npm run setup
#   ↓
#   npm'nin package.json'daki "setup" scripti çalıştır
#   (Gerekli kütüphaneler ve dosyalar otomatik yüklenir)