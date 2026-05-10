
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


# ----Subject diagram---
- Sonuç: Subjec'teki diyagram Docker kullanılarak kurulmuş bir WordPress web sitesinin mimarisini adım adım gösteriyor.

Bu yapı, **Docker içinde çalışan bir WordPress sitesinin sistem mimarisidir.** Ana bilgisayar (host) üzerinde Docker çalışır ve içinde üç ayrı container bulunur: **NGINX, WordPress (PHP), MariaDB**. Bu container’lar birbirinden izole çalışır ama aynı Docker ağı içinde birbirleriyle haberleşir.

Kullanıcı tarayıcıdan siteye girdiğinde istek internet üzerinden **443 portuyla (HTTPS)** önce **NGINX** container’ına gelir. NGINX burada dış dünyaya açılan kapıdır. Gelen isteği karşılar, statik dosyaları (resim, CSS, JS) kendisi sunar. Eğer istek WordPress sayfasıysa bunu **9000 portu üzerinden WordPress + PHP-FPM** container’ına iletir.

WordPress container’ı sitenin asıl beynidir. Yazılar, sayfalar, kullanıcı girişleri, eklentiler ve tüm site mantığı burada çalışır. Eğer veri gerekiyorsa **3306 portu üzerinden MariaDB veritabanına bağlanır.** Veritabanından yazıları, ayarları veya kullanıcı bilgilerini çeker. Sonra HTML sayfayı oluşturur ve tekrar NGINX’e gönderir. NGINX de bunu ziyaretçiye gösterir.

MariaDB container’ı sitenin hafızasıdır. İçinde yazılar, kullanıcı hesapları, şifreler, yorumlar ve ayarlar tutulur. Dışarıdan internete açık değildir; sadece WordPress erişebilir. Bu da güvenlik sağlar.

Ayrıca sistemde **Volumes (kalıcı depolama)** bulunur. Bunlar sayesinde container silinse bile veriler kaybolmaz. Veritabanı verileri ayrı volume’da tutulur. WordPress tema, eklenti ve yüklenen resimler de başka bir volume’da saklanır.

Kısaca:

* **NGINX = Kapı / Trafik yöneticisi**
* **WordPress = Beyin / Siteyi oluşturan sistem**
* **MariaDB = Hafıza / Verileri saklayan yer**
* **Docker Network = İç iletişim ağı**
* **Volumes = Kalıcı disk alanı**

Yani bu yapı hızlı, güvenli, düzenli ve taşınabilir bir WordPress sunucu sistemidir.
