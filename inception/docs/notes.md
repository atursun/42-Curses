# Notlar

1. Sanallaştırma:
Sanal makineler, Fiziksel bir bilgisayar üzerinde kurulan sanal makinelerdir/ortamdır.
Bu sanal ortamlar tamamen izole bir şekilde çalışarak fiziksel makinenin donanımlarını (CPU,RAM, vb.) kullanır. sanal makineler fiziksel makineyi taklit eder. yani bilgisayarın için de kurduğumuz bilgisayardır. her sanal ortamın farklı bir işletim sistemi, dosya yapısı, süreci olabilir. Bir sanal ortamda yapılan değişiklik diğer sanal makineleri veya ana bilgisayarı etkilemez. bir sanal makine çökerse diğerleri çökmez. çünkü izole bir şekilde çalışır. yani, fiziksel makineden bağımsız çalışıyorlar. Sanal makine kullanmamızın sebebi ise, farklı işletim sistemleri denemek istiyorsak, yada güvenlik amacıyla dosyaları/programları ana cihazda değil de sanal ortamda açmak istiyorsak. Sanal makineler, Hypervisor denilen ana bilgisayarın donanımını sanal makinelere dağıtarak her birinin bağımsız ve izole şekilde çalışmasını sağlar. Sanal Makinenin amacı ise, Bir fiziksel sunucunun/bilgisayarın işlemci gücü, bellek kapasitesi ve depolama alanı gibi kaynakları genelde tam kapasite kullanılmaz. Sanal makineler, bu kaynakları bölerek birden fazla görev için kullanılabilir hale getirir. Sonuç; Tek bir fiziksel sunucunun kaynaklarını verimli bir şekilde birden fazla göreve bölersiniz. Böylece, hem maliyet düşer hem de verim artar.

2. ISO Dosyası:
bir disk veya işletim sisteminin dijital kopyasıdır. İçerisinde işletim sisteminin dosyaları, kurulum verileri, sistem dosyaları ve genellikle önyükleme için gerekli dosyalar bulunur. Bu, bir CD, DVD (Veri Depolama) veya USB'ye yazılarak fiziksel bir disk gibi kullanılabilir.

3. Vm **skip unattended installation**:
Bu seçeneği seçmek, otomatik kurulum adımlarını atlamayı sağlar.
Bu durumda kurulum manuel olarak yapılır.
Kullanıcı her adımı kendisi seçer ve onaylar.
Böylece hangi paketlerin ve ayarların kurulacağını kontrol edebilirsin.

4. Hard Disk File Type and Variant:
- Sanal Disk Türü -> Sanal makinede disk oluştururken seçtiğin dosya formatıdır.
    - VDI (VirtualBox Disk Image) → VirtualBox’a özel, esnek ve değiştirilebilir.
- Disk Tipi -> Diskin gerçek diske nasıl kaydedileceğini belirler
    - Dynamically allocated (Dinamik) → Disk büyüdükçe yer kaplar, başta az yer kullanır.
    - Fixed size (Sabit boyut) → Disk başta belirlenen boyutta yer kaplar, biraz daha hızlı.

5. Hostname && Domain Name:
- Hostname → Sanal makinenin/Cihazın/Bilgisayarın kendi adıdır.
Domain name → bir bilgisayarın veya servisin ağ üzerinde tanınmasını sağlayan isimdir.
Örneğin web sitelerinde **example.com** gibi yazılır.

6. Partition Disk:
Diskin mantıksal parçalara ayrılmasıdır. yani belirlediğin pathlere (root: 20GB, home: 5GB) şeklinde ayırmandır. Bu manuel seçeneğidir. eğer *use entire disk* dersen kurulum disk bölümleri kurulum tarafından oluşturulur.

7. GRUB Boot Loader:
GRUB, Linux’un açılmasını sağlayan önyükleyici yazılımdır. Debian kurulumunda GRUB’u yükleyerek VM’in hangi işletim sistemini başlatacağını belirledin. “sda” seçerek, GRUB’u sanal diskin ana alanına (MBR) yükledin. Bu sayede VM açıldığında otomatik olarak Debian başlatılacak. Eğer GRUB kurulmazsa, VM açıldığında işletim sistemi yüklenemez ve hata verir.

8. Snapshot:
Yani işletim sistemi, dosyalar, ayarlar ve programlar tam olarak o anki şekilde kaydedilir.
Eğer sonra bir şeyler bozulursa veya yanlış bir şey yaparsan, snapshot’ı geri yükleyerek VM’yi o ana geri alabilirsin.
Gerçek hayatta bir “fotoğraf” gibi düşünebilirsin, her şeyi dondurur ve istediğinde tekrar açabilirsin.

9. Servis:
Servis, bir makinenin arka planında sürekli çalışan ve bir iş yapan programdır.
Servisler, sen istemeden de çalışırlar, beklerler, istek gelince yanıt verirler


10. Server (Sunucu):
Sunucu, Bir ağ üzerinde, istemcilerden (client) gelen istekleri karşılayıp yanıt veren donanım veya yazılımdır. "İstek bekleyen, istek gelince hizmet veren taraf."
Sunucu (server), diğer bilgisayarlara hizmet sağlayan bir bilgisayardır. Kullanıcıların kullandığı cihazlar istemci (client) olarak adlandırılır ve sunucuya istek gönderir; sunucu da bu isteklere cevap verir. Örneğin bir web sitesine girdiğinde sunucu sana siteyi gönderir, oyun oynarken sunucu oyuncuları birbirine bağlar, dosya indirirken sunucu dosyayı iletir. Gerçek hayatta bir restorandaki mutfak gibi düşünülebilir: müşteri sipariş verir, mutfak hazırlar ve sunar. Sunucular farklı amaçlara göre türlere ayrılır; web sunucuları siteleri çalıştırır, veritabanı sunucuları verileri saklar, oyun sunucuları oyuncuları yönetir ve dosya sunucuları dosya paylaşımı yapar.
Sunucu (server) dediğin şey aslında tek bir program değil, birlikte çalışan servislerin oluşturduğu bir sistemdir.

11. Bridged Adapter:
sanal makinenin modemden gerçek bir cihaz gibi IP almasını sağlar. Böylece VM, aynı ağda ayrı bir bilgisayar gibi görünür ve ana bilgisayardan doğrudan SSH ile bağlanabilirsin. NAT’a göre daha kolay ve direkt bağlantı sağlar.

12. conf dosyası:
Config dosyası, bir programın nasıl çalışacağını belirleyen ayar dosyasıdır. yani, Programın “kuralları ve ayarları”dır. örneğin bir web sunucusunun (nginx); config dosyası şunu söyler: 
- hangi portta çalışacak? (80 / 443)
- Hangi klasörden siteyi gösterecek?
- Hangi domain için çalışacak?
- PHP varsa nasıl işleyecek?

13. Domain–IP Bağlantısı:
127.0.0.1 -> atursun.42.fr
- Bu satır şu demek; "atursun.42.fr domaini aslında bu bilgisayara (localhost) ait"
Tarayıcı Normalde Ne Yapar, Sen tarayıcıya şunu yazdığında: https://atursun.42.fr
Normalde şu olur: DNS’e gider, "Bu domainin IP’si ne?" diye sorar, IP bulur, O IP’ye bağlanır
Ama Senin Durumunda, Bu domain gerçek bir domain değil; DNS’te yok ❌, İnternette karşılığı yok ❌
Bu yüzden çözümü şudur: "/etc/hosts"
Bu dosya local DNS gibi çalışyor.
127.0.0.1 atursun.42.fr -> yaptığımızda, Bunun anlamı, 
| Domain        | IP        |
| ------------- | --------- |
| atursun.42.fr | 127.0.0.1 |

Gerçek Akış

Şimdi kullanıcı yazıyor: https://atursun.42.fr

Sistem şöyle çözüyor:
- /etc/hosts kontrol edilir
- eşleşme bulunur ✅
- IP → 127.0.0.1
- bağlantı → kendi bilgisayarına gider

14. TLS (Transport Layer Security) / SSl:
TLS (Transport Layer Security) — eski adıyla SSL — istemci (tarayıcı) ile sunucu (NGINX) arasındaki iletişimi şifreleyen ve kimlik doğrulayan bir güvenlik katmanıdır. Amaç; gönderilen verilerin üçüncü kişiler tarafından okunamaması (gizlilik), değiştirilmemesi (bütünlük) ve gerçekten doğru sunucuya bağlanıldığının doğrulanmasıdır (kimlik doğrulama).


15. git rm --cached <dosya> -> uzak repodaki bir dosyası siler. sonra localde commit yapıp push yapman gerekiyor.





