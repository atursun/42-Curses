# FDF Projesi: Harita ve Koordinat Sistemi Analizi

Bize verilen map (.fdf) 3 Boyutlu bir haritadır. ve 3D bir haritayı 2D ekrana çizmemiz gerekiyor
Bir verinin 3 boyutlu olması için 3 eksene ihtiyacı vardır: En (x), Boy (y) ve Yükseklik (z)
Eğer dosyadaki sayıların hepsi birbirinin aynısı olsaydı (örneğin hepsi 0), o zaman sonuç dümdüz bir 2D yüzey olurdu. Ancak 42.fdf dosyasında 0 (zemin) ve 10 (tepe) değerleri olduğu için harita hacim kazanır ve 3 boyutlu bir yapıya dönüşür.

Bu belge, `.fdf` dosya formatının yapısını, koordinat sistemlerini ve projenin matematiksel temelini açıklar.

<!-- --ben seni daha çok seviyorum :) -->

## 1. Girdi Dosyası (.fdf) Yapısı

FDF projesi, metin tabanlı harita dosyalarını okuyarak çalışır.

*   **İçerik:** Her sayı bir noktayı temsil eder.
    *   **Yatay konum:** Sütun sırası (X)
    *   **Dikey konum:** Satır sırası (Y)
    *   **Sayısal değer:** Yükseklik/Altitude (Z)
    *   **(Opsiyonel) Renk:** Hexadecimal formatında verilebilir (örn: `10,0xFF0000`).

---

## 2. Koordinat Sistemleri: 2D vs 3D

Projenin temel amacı, 3 boyutlu veriyi/haritayı 2 boyutlu ekrana çizmektir.

### A. 2D Sistem (İki Boyutlu)
*   **Nedir:** Düz bir zemindir (Kağıt, Ekran).
*   **Eksenler:**
    *   `x`: Yatay (Sağ/Sol)
    *   `y`: Dikey (Yukarı/Aşağı)
*   **Temsil:** `(x, y)`
*   **Hacim:** Yoktur, sadece alan vardır.

### B. 3D Sistem (Üç Boyutlu)
*   **Nedir:** Gerçek dünya veya uzay boşluğudur.
*   **Eksenler:** 2D'ye "derinlik" eklenir.
    *   `x`: Genişlik
    *   `y`: Yükseklik
    *   `z`: Derinlik (Bize yakınlık/uzaklık veya yükseklik)/(dosyadaki her sayı Z temsil eder)
*   **Temsil:** `(x, y, z)`
*   **Hacim:** Vardır (Küp, Küre vb.).

---

## 3. FDF Koordinat Mantığı (x, y, z)

Harita dosyasını okurken her sayı 3 boyutlu bir noktaya dönüşür. Dönüşüm kuralı şöyledir:

`Dosyadaki Konum` ➔ `(x, y, z)`

### X Değeri (Sütun / Column)
*   **Nedir:** Harita üzerindeki **yatay** konumdur.
*   **Nereden Gelir:** Okunan satırda sayının kaçıncı sırada olduğu (sütun indeksi).

### Y Değeri (Satır / Row)
*   **Nedir:** Harita üzerindeki **dikey** konumdur.
*   **Nereden Gelir:** Dosyanın kaçıncı satırının okunduğu.

### Z Değeri (Yükseklik / Altitude)
*   **Nedir:** Noktanın yerden yüksekliğidir.
*   **Nereden Gelir:** Dosyada yazan **sayının kendisidir**.

---

## 4. Pratik Analiz: `42.fdf` Dosyası

Örnek `42.fdf` dosyasının teknik analizi şöyledir:

*   **Genişlik (X ekseni):** 19 nokta
*   **Yükseklik (Y ekseni):** 11 satır
*   **Min Z Değeri:** 0 (Taban/Zemin)
*   **Max Z Değeri:** 10 (Tavan/Zirve)
*   **Renk Bilgisi:** Yok (Sadece ham yükseklik verileri var).

**Görsel Sonuç:**
Ekrana çizildiğinde `0` değerleri düz bir zemin oluştururken, `10` değerleri bu zeminden yukarı doğru aniden yükselen duvarlar oluşturarak "42" sayısını meydana getirir.

---

## 5. Renk ve Veri Formatı Analizi

FDF dosyalarında renk bilgisi **opsiyoneldir**. Programımız her iki durumu da yönetebilmelidir:

*   **Mantık:** Haritada özel bir renk kodu varsa o kullanılır, yoksa varsayılan bir renk (genellikle Beyaz) atanır.

Parsing (ayrıştırma) sırasında karşılaşacağımız iki veri tipi şunlardır:

### Tip A: Sadece Yükseklik (Standart)
*   **Örnek Veri:** `10`
*   **Anlamı:** `Z = 10`
*   **Renk Durumu:** Renk belirtilmediği için varsayılan renk atanır.

### Tip B: Yükseklik + Renk (Özel)
*   **Örnek Veri:** `20,0xFF0000`
*   **Anlamı:** `Z = 20`
*   **Renk Durumu:** Virgül (`,`) ayracından sonraki hex kodu (`0xFF0000`) okunur ve o nokta bu renge boyanır.