
# Projeyi açıklama şekli

## Inception Projesi Nedir
Docker teknolojisini kullanarak, birden fazla servisten oluşan bir sistem (wordpress/web altyapısı) kurmak ve bu sistemi yönetmektir.
servislerin hepsi birlikte çalışacak.
- Tüm servisleri tek tek 'docker run' komutu ile aya kaldırmaktansa .yml dosyası ile tek komutla servisler ayağa kaldırılmalıdır.
- her servis ayrı containerda olacak, image isimleri servis adıyla aynı olacak, hazır image çekmek (pull) yasak bunun yerine kendi Dockerfile'ını yazacakasın.

## Docker nedir (docker, container, network, volume, .yml, docker kavramları...)
[Buraya Bak](./docs/docker.md) 


## sistem mimarisi
- İstek akışı: Kullanıcı → DNS → NGINX → PHP-FPM → WordPress → MariaDB

## servisler (nginx, wordpress, mariadb)
- .sh dosyaları
- Dockerfile dosyaları
- .conf dosyaları



## wp-admin üzerinden örnek gösterme (post, page oluşturma, kullanıcı oluşturup silme...)



----------

- TCP -> bilgisayarlar veya cihazlar arasında güvenilir veri iletimi sağlayan bir iletişim yöntemidir.
