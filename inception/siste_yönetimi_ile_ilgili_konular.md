# 🚀 Inception Projesi - Sistem Yönetimi Rehberi

> Bu proje **orta-ileri seviye** sistem yönetimi konularını kapsamlı şekilde kapsayan bir DevOps eğitim projesidir.

---

## 📋 İçindekiler

- [Ana Kapsam Alanları](#-ana-kapsam-alanları)
- [Zorluk Seviyesi](#-zorluk-seviyesi-dağılımı)
- [Öğrenme Yol Haritası](#️-öğrenme-yol-haritası)
- [Öğrenme Çıktıları](#-öğrenme-çıktıları)
- [Sertifikasyon](#-sertifika-yolu)
- [Zaman Planlaması](#️-tahmini-tamamlanma-süresi)

---

## 🎯 Ana Kapsam Alanları

### 1. Konteynerizasyon & Sanallaştırma ⭐⭐⭐

**Önem Derecesi:** Yüksek

- Docker ekosistemi
- Container yönetimi
- Image oluşturma (Dockerfile)
- Docker Compose orchestration
- Container networking
- Volume yönetimi

### 2. Web Sunucu Yönetimi ⭐⭐⭐

**Önem Derecesi:** Yüksek

- NGINX yapılandırması
- TLS/SSL sertifika yönetimi (TLSv1.2/1.3)
- Reverse proxy kurulumu
- Port yönetimi (443)

### 3. Veritabanı Yönetimi ⭐⭐

**Önem Derecesi:** Orta

- MariaDB kurulumu ve yapılandırması
- Kullanıcı ve yetki yönetimi
- Veritabanı güvenliği
- Persistent storage

### 4. Uygulama Dağıtımı ⭐⭐

**Önem Derecesi:** Orta

- WordPress kurulumu
- PHP-FPM yapılandırması
- Multi-tier architecture

### 5. Güvenlik ⭐⭐⭐

**Önem Derecesi:** Yüksek

- Docker Secrets
- Environment variables
- Credential yönetimi
- TLS/SSL encryption
- Network isolation

### 6. Network Yönetimi ⭐⭐

**Önem Derecesi:** Orta

- Docker networking
- Container iletişimi
- DNS yapılandırması
- Port mapping

### 7. DevOps Pratikleri ⭐⭐

**Önem Derecesi:** Orta

- Infrastructure as Code
- Automation (Makefile)
- Version control best practices
- Documentation

---

## 📊 Zorluk Seviyesi Dağılımı

| Seviye | Dağılım | Açıklama |
|--------|---------|----------|
| **Başlangıç** | `▓░░░░` 20% | VM kurulumu, temel Linux komutları |
| **Orta** | `▓▓▓░░` 60% | Ana proje gereklilikleri |
| **İleri** | `▓▓░░░` 40% | Bonus özellikler ve optimizasyon |

---

## 🗺️ Öğrenme Yol Haritası

### Ön Gereksinimler (Seviye 1-2)

Bu projeye başlamadan önce aşağıdaki konularda temel bilgiye sahip olmalısınız:

- ✅ Linux komut satırı kullanımı
- ✅ Temel networking kavramları
- ✅ Bash scripting temelleri

### Bu Projede Öğrenecekleriniz

- 🎯 Docker ekosistemi ve container teknolojileri
- 🎯 Container orchestration
- 🎯 Mikroservis mimarisi temelleri
- 🎯 SSL/TLS yapılandırması

### Sonraki Adımlar

Projeyi tamamladıktan sonra bu konulara geçebilirsiniz:

- ➡️ **Kubernetes** - Container orchestration
- ➡️ **CI/CD Pipelines** - Otomasyon ve deployment
- ➡️ **Cloud Platforms** - AWS, Azure, GCP

---

## 💡 Öğrenme Çıktıları

### Teknik Beceriler

- Dockerfile yazma ve optimizasyon
- Docker Compose ile multi-container uygulamalar
- Volume ve network yönetimi
- Container güvenliği

### Sistem Yönetimi

- Service isolation ve container best practices
- Security best practices
- Persistent data yönetimi
- Troubleshooting ve debugging

### DevOps Felsefesi

- Infrastructure as Code (IaC)
- Automation ve scripting
- Comprehensive documentation
- Version control best practices

---

## 🎓 Sertifika Yolu

Bu projeye hazırlanmak için önerilen sertifikasyonlar:

| Sertifika | Açıklama | Durum |
|-----------|----------|-------|
| **Docker Certified Associate (DCA)** | Docker ekosistemi ve container yönetimi | ✅ Önerilir |
| **CompTIA Linux+** | Linux sistem yönetimi temelleri | ✅ Önerilir |

---

## ⏱️ Tahmini Tamamlanma Süresi

| Aşama | Süre | Açıklama |
|-------|------|----------|
| **Hazırlık** | 2-3 hafta | Docker ve container teknolojilerini öğrenme |
| **Proje (Zorunlu)** | 2-4 hafta | Ana proje gereksinimlerini tamamlama |
| **Bonus** | 1-2 hafta | Opsiyonel bonus özellikleri |
| **TOPLAM** | **5-9 hafta** | Günde 2-4 saat çalışma ile |

---

## 📚 Ek Kaynaklar

### Önerilen Okuma Listesi

- Docker resmi dokümantasyonu
- NGINX yapılandırma rehberi
- MariaDB administration guide
- WordPress deployment best practices

### Faydalı Komutlar

```bash
# Docker container'larını listele
docker ps -a

# Docker Compose ile projeyi başlat
docker-compose up -d

# Log'ları görüntüle
docker-compose logs -f

# Container'ları durdur ve temizle
docker-compose down -v
```

---

**Son Güncelleme:** 2026
**Versiyon:** 1.0