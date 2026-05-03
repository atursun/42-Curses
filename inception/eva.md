
# Inception Projesi Nedir
Docker teknolojisini kullanarak, birden fazla servisten oluşan bir sistem kurmak ve bu sistemi yönetmektir.
servislerin hepsi birlikte çalışacak.
- Tüm servisleri tek tek 'docker run' komutu ile aya kaldırmaktansa .yml dosyası ile tek komutla servisler ayağa kaldırılmalıdır.
- her servis ayrı containerda olacak, image isimleri servis adıyla aynı olacak, hazır image çekmek (pull) yasak bunun yerine kendi Dockerfile'ını yazacakasın.


# Evalde Sorulan / Anlattırılan Konular
Öğrenciye özellikle şunları basitçe açıklatması isteniyor:
    Docker ve Docker Compose nasıl çalışır?
    Compose ile image kullanımı / compose’suz kullanım farkı nedir?
    Docker’ın VM’e göre avantajı nedir?
    Projedeki dizin yapısının (subjectteki yapı) neden mantıklı olduğu.
    Docker network nedir, neden kullanılır?
    MariaDB’ye nasıl login olunur, kullanıcı/şifre mantığı nasıl.

# docker network drives (sürücüleri/bridge...)