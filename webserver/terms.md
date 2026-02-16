
# Blocking && Non-Blocking Server Mantığı
Blocking ve Non-Blocking sever mantığı, aslında sunucunun **aynı anda** gelen istekleri nasıl yönettiğidir.

## 1. Blocking (Bloklayan) Server Mantığı
Server bir isteği işlerken diğer istekleri bekletir. İş bitince diğer isteklere geçer.
Ama çok fazla istek gelirse server bunu yönetmeyebilir ve çökebilir.
Bekleme süresi performansı düşürür.

## 2. Non-Blocking (Bloklamayan) Server Mantığı
Server bir isteği işlerken boş durmaz, diğer işlere geçer.
peki nasıl yapar, *soket* kullanılarak. soketler istekleri bloke etmez
veri yoksa beklemek yerine devam eder.
aynı anda binlerce isteği işleyebilir ve daha performanslıdır.

