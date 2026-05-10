# Projenin amacı;

**3 temel servis:**

1. **NGINX** — Tek giriş noktası (port 443, TLS ile)
2. **WordPress + php-fpm** — Web uygulaması
3. **MariaDB** — Veritabanı

Ve bunları birbirine bağlayan bir **Docker network**, verilerin kaybolmaması için de **2 adet named volume** (biri WordPress dosyaları, biri veritabanı için).

Yani mimari şöyle akar:

```
Kullanıcı → NGINX (443) → WordPress → MariaDB
```

Her servis kendi container'ında izole çalışıyor, ama aynı network üzerinden birbirini görebiliyor. Temel fikir bu kadar basit aslında — geri kalan her şey (Dockerfile yazmak, .env, secrets, Makefile) bu üç servisin doğru kurulması için gereken altyapı.


# Problem
1. nginx ve wordpress'in ortak volume olmamamsı:
Kullanıcı senin portuna giriyor (443), Nginx, karşılayıp sertifikayı hallediyor. Ardından "/var/www/html klasöründeki index.php dosyasını getireyim" diyor. Kendi klasörüne bakıyor ama WordPress dosyaları orada yok (WordPress kendi container'ında hapiste kaldı). İsteği proxy ile 9000 portuna (WordPress'e) yollasa da, SCRIPT_FILENAME eşleşmediği için "File not found." veya "404" hatası patlıyor.


# Proje adımları
Projeyi yaparken attığın adımlar ve öğrendiğin şeylerin listesi/adımları
d
1. sanal makine de SİSTEM KURULUMU yaptık

2. sonrasında SİSTEM YAPILANDIRILMASI yaptık
	- sudo kurulumu, kullanıcıyı sudo grubuna ekleme ve tam yetkilendirme
	- ekranı tam yapma (guest edition/display settings)
	- gerekli paketlerin/servislerin kurulumu (git, vscode, docker.io, docker-compose, ssh)
