Bİr domaine istek attığımda, site (Nginx) tarayıcıya bir SSL/TLS sertifikası sunar. Tarayıcı bu sertifikanın geçerliliğini ve hangi kurum tarafından imzalandığını kontrol eder. Eğer sertifika, tarayıcının güvenilir kabul ettiği bir Certificate Authority (CA) tarafından imzalanmamışsa “güvenilir değil” uyarısı gösterir. https://atursun.42.fr adresinde bu uyarıyı görmemin temel nedeni, sertifikanın self-signed olmasıdır.

domaine istek attığımda bana "güvenilir değil" diye bir yazı çıkarıyor firefox. bunun sebebi ise sertifikanın self-signed (kendi kendine) imzalanmış olmasıdır. eğer "güvenilir değil" hatası almak istemiyorsak, CA (Certificate Authority) sertifika otoritesi tarafından sertifikayı imzalatmamız gerekiyor (yani, bu domainin benim olduğunu doğrulamam gerekiyor. bu domain gerçekten de benim kontrolüm de mi). örnek otorite (lets encrypt)


# NGINX
Kullanıcı tarayıcıya bir URL yazıp isteği gönderdiğinde süreç DNS çözümlemesi ile başlar. Tarayıcı, domain adının hangi IP adresine karşılık geldiğini DNS sunucusundan öğrenir ve bu IP adresine bağlanır. Bağlantı kurulduktan sonra istek Nginx sunucusuna ulaşır. Nginx burada bir ön kapı (gateway) gibi çalışır.
Eğer istek HTTPS üzerinden geliyorsa Nginx önce SSL/TLS sürecini yönetir. Güvenli bağlantıyı kurar, sertifikayı doğrular ve şifreli iletişimi başlatır. Ardından gelen isteğin türünü analiz eder. Eğer istek statik bir dosyaya aitse (örneğin CSS, JavaScript, görsel, font veya düz HTML dosyası) bu dosyayı doğrudan kendisi sunar. Bu işlem çok hızlıdır çünkü herhangi bir arka plan uygulaması çalıştırılmaz.
Eğer istek dinamik bir içeriğe aitse (örneğin WordPress sayfası veya PHP dosyası) Nginx bu içeriği çalıştıramadığı için isteği PHP-FPM servisine yönlendirir.   
PHP-FPM, PHP kodlarını çalıştıran bir işleme katmanıdır. Gelen isteğe göre ilgili PHP dosyasını işler, gerekli hesaplamaları yapar ve gerekiyorsa veritabanı ile iletişime geçer. İşlem tamamlandıktan sonra çıktıyı Nginx’e geri gönderir. Nginx de bu sonucu kullanıcıya iletir.

# WORDPRESS VE PHP-FPM
WordPress, PHP tabanlı bir web uygulamasıdır ve sunucu üzerinde çalışan dosya ve klasörlerden oluşur. Temel yapısı PHP dosyaları (index.php, wp-login.php, wp-admin gibi), sistem klasörleri (wp-includes, wp-admin), içerik klasörü (wp-content içinde tema, eklenti ve medya dosyaları) ve yapılandırma dosyası (wp-config.php) şeklindedir. Bu dosyalar genellikle /var/www/html dizininde bulunur.
PHP-FPM, WordPress’in PHP kodlarını çalıştıran motor olarak görev yapar. Nginx doğrudan PHP çalıştıramadığı için bu sorumluluğu PHP-FPM üstlenir.
WordPress’in çalışma süreci şu şekilde ilerler: Nginx PHP isteğini PHP-FPM’e iletir, PHP-FPM ilgili WordPress dosyasını çalıştırır, WordPress gerekli verileri almak için MariaDB veritabanına bağlanır, veritabanından gelen bilgiler işlenerek HTML çıktı üretilir, bu çıktı PHP-FPM tarafından Nginx’e geri gönderilir ve Nginx sonucu kullanıcıya iletir.

# MARIADB (VERİTABANI)
MariaDB, WordPress’in veri katmanıdır. Tüm dinamik içerikler burada saklanır. Site ayarları, yazılar, sayfalar, kullanıcı hesapları, yorumlar, menüler ve tema/eklenti yapılandırmaları MariaDB içinde tutulur.
Kullanıcı bir sayfa açtığında WordPress, gerekli bilgileri almak için MariaDB’ye SQL sorguları gönderir. MariaDB bu sorgulara karşılık verileri döner ve WordPress bu verileri kullanarak HTML çıktısını oluşturur.


#GENEL SİSTEM AKIŞI#
Sistem genel olarak şu şekilde çalışır: Kullanıcı isteği gönderir, DNS bu isteği IP adresine çevirir, Nginx isteği karşılar ve yönlendirir, statik içerik varsa doğrudan sunar, dinamik içerik varsa PHP-FPM’e iletir, PHP-FPM WordPress’i çalıştırır, WordPress MariaDB’den veri çeker, sonuç HTML olarak üretilir ve Nginx üzerinden kullanıcıya geri gönderilir.
