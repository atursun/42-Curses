# inception (9 nisanda projeye başlandı)

# Proje Bittikten Sonra Ne Yapmış Oluyorum ?
Bu projede, bir sanal makine üzerinde Docker kullanarak çalışan bir web altyapısı kurmuş olacaksın.
NGINX, WordPress ve MariaDB servislerini ayrı container’larda çalıştırıp birbirine bağlamış olacaksın.
Sistemi HTTPS (TLS) ile güvenli hale getirip tek giriş noktası oluşturmuş olacaksın.
Verileri volume kullanarak kalıcı hale getirmiş ve servisleri otomatik yönetilebilir yapmış olacaksın.
Sonuç olarak, gerçek hayattaki bir web sunucu altyapısını sıfırdan kurmayı öğrenmiş olacaksın.
"Ben sadece bir web sitesi kurmadım, o web sitesini çalıştıran tüm sistemi kurdum"







# ÖNEMLİ

Kendi bilgisayarımdakiler
----
hostname -> abdullah
domain-name -> atursun.42.fr
root password -> 2332
username -> apo | şifresi -> 233


# ----Subject---

######
- Sonuç: Subjec'teki diyagram Docker kullanılarak kurulmuş bir WordPress web sitesinin mimarisini adım adım gösteriyor.

Bu diyagram **Docker kullanılarak kurulmuş bir WordPress web sitesinin mimarisini** adım adım gösteriyor. Baştan sona, dış dünyadan (internet) verinin nasıl gelip WordPress’in nasıl çalıştığını çok net şekilde açıklayayım.

---

## 🖥️ 1. Computer HOST (Ana Makine)

En dış çerçevede gördüğün **Computer HOST**, senin gerçek sunucun ya da bilgisayarın:

* Fiziksel makine veya VPS
* Docker burada çalışıyor
* Tüm container’lar bu makinenin içinde

> Yani Docker, bu host üzerinde izole mini sistemler (container’lar) çalıştırıyor.

---

## 🌐 2. WWW (İnternet) → NGINX (443)

En üstte **WWW** var:

* Kullanıcı tarayıcıdan siteye giriyor
  👉 `https://siteadi.com`

Bu istek:

* **443 portu** üzerinden geliyor (HTTPS)

⬇️
Bu istek doğrudan **NGINX container**’ına ulaşıyor.

> 🔒 443 = HTTPS
> NGINX burada **kapı görevlisi (reverse proxy)** gibi çalışıyor.

---

## 📦 3. Docker Network (Özel İç Ağ)

Gri alanın tamamı **Docker network**:

* Container’lar **aynı özel ağ içinde**
* Dışarıdan doğrudan erişilemezler
* Birbirleriyle **container isimleri üzerinden** haberleşirler

Bu ağ içinde 3 ana container var:

---

## 🧱 4. Container NGINX (Web Server)

**Görevi:**

* İnternetten gelen istekleri almak
* HTML, CSS, JS gibi statik dosyaları sunmak
* PHP isteklerini WordPress-PHP container’ına yönlendirmek

**Bağlantı:**

* WordPress-PHP ile **9000 portu** üzerinden konuşur

```text
NGINX ──(9000)──> WordPress + PHP-FPM
```

> NGINX PHP çalıştırmaz, sadece yönlendirir.

---

## 🐘 5. Container WordPress + PHP

**Görevi:**

* WordPress’in kendisi burada
* PHP kodları burada çalışır
* Kullanıcının istediği sayfayı oluşturur

**İki yönlü bağlantısı var:**

### 🔁 NGINX ile:

* PHP isteklerini alır
* HTML çıktısını NGINX’e geri gönderir

### 🔁 DB ile:

* Yazılar, kullanıcılar, ayarlar için veritabanına bağlanır
* **3306 portu** kullanılır

```text
WordPress ──(3306)──> Database
```

---

## 🗄️ 6. Container DB (Veritabanı – MySQL/MariaDB)

**Görevi:**

* WordPress verilerini saklar:

  * Yazılar
  * Kullanıcılar
  * Şifreler
  * Ayarlar

**Önemli nokta:**

* Dış dünyaya açık **DEĞİL**
* Sadece WordPress container erişebilir

---

## 💾 7. Volumes (Kalıcı Veri)

Altta gördüğün silindirler **Volume**’leri temsil eder.

### 📌 DB Volume

* Veritabanı verileri burada tutulur
* Container silinse bile:

  * Yazılar
  * Kullanıcılar
    **kaybolmaz**

### 📌 WordPress Volume

* `wp-content` klasörü
* Tema, eklenti, yüklenen görseller burada

> Volume = **Docker container ölse bile veri yaşar**

---

## 🔌 8. Portlar Ne Anlama Geliyor?

| Port | Nerede            | Anlamı  |
| ---- | ----------------- | ------- |
| 443  | WWW → NGINX       | HTTPS   |
| 9000 | NGINX → WordPress | PHP-FPM |
| 3306 | WordPress → DB    | MySQL   |

---

## 🔄 9. Bir Kullanıcı Siteye Girdiğinde Ne Olur?

1. Tarayıcı → `https://site.com`
2. İstek **443** ile NGINX’e gelir
3. NGINX:

   * Statik dosya ise kendisi verir
   * PHP ise WordPress’e yollar
4. WordPress:

   * Gerekirse DB’den veri çeker
   * Sayfayı oluşturur
5. HTML çıktı:

   * WordPress → NGINX → Kullanıcı

---

## 🎯 Diyagramın Özeti (Tek Cümle)

> Bu mimaride **NGINX dış dünyaya açılan kapı**, **WordPress beynin kendisi**, **Database hafıza**, **Docker network özel iç yol**, **Volume ise kalıcı depodur**.
