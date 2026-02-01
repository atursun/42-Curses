# İzometrik Projeksiyon Nedir?

**İzometrik Projeksiyon**, 3 boyutlu bir nesneyi/haritayı 2 boyutlu bir yüzeyde (ekranda) sanki 3D imiş gibi göstermenin matematiksel bir hilesidir.
Yani, 3D noktaları 2D ekrana yansıtan bir teknik
Ama bunu yaparken nesnenin üç eksenini de eşit açıyla gösterir.
Kısacası, 3D `(x, y, z)` noktalarını alıp özel bir açıyla bükerek 2D `(x, y)` ekran koordinatlarına dönüştüren tekniktir.
- Projeksiyon (İzdüşüm), bir nesnenin görüntüsünü belirli bir bakış açısından bir yüzeye (genellikle düzleme) aktarma işlemidir. (Yani, Çok boyutlu bir şeyi, az boyutlu bir yere çizmektir. örn izometrik projeksiyon)
- Perspektif, insan gözünün dünyayı algılama biçimidir. Nesnelerin göze olan uzaklığına göre görünümünün değişmesidir. Temel Kuralı: Bir nesne bizden ne kadar uzaklaşırsa, o kadar küçük görünür.
İzometrikte uzaktaki nesne küçülmez (boyutu aynı kalır), perspektifte ise küçülerek gerçekçilik sağlanır. (Örnek: Tren raylarının ufukta birleşiyormuş gibi görünmesi).

---

## Neden "İzometrik"?
Kelime Yunanca "eşit ölçü" anlamına gelir.
*   **Perspektif Yoktur:** Gerçek hayatta uzaktaki nesneler küçük görünürken, izometrik projeksiyonda **uzaklık algısı yoktur.**
*   **Paralellik:** Nesne ne kadar uzakta olursa olsun boyutu değişmez ve paralel çizgiler her zaman paralel kalır.

## Görsel Özeti
*   **Normal (2D):** Kare tam karşıdan görünür `⬜`
*   **İzometrik (3D):** Kare baklava dilimi gibi görünür `🔶`

Bu sayede ekranda hem zemini, hem duvarları, hem de tavanı aynı anda görebiliriz.

---

## Nasıl Çalışır? (Formül ve Matematik)

3D dünyadaki bir `(x, y, z)` noktasını 2D ekrana yansıtmak için eksenleri belirli bir açıyla **(genellikle 30 derece)** bükmemiz gerekir. Bu işlem sonucunda 3 eksen ekranda **eşit açılarla (120°)** görünür ve 3D hissi oluşur.

### İzometrik Projeksiyon Formülü

Kod yazarken kullandığımız dönüşüm formülü şudur:

1.  **x eksenini bükmek (Yatay açılma):**
    ```math
    x_2d = (x - y) * cos(30°)
    ```
    *Görünüm: Sağ alt çapraz.*

2.  **y eksenini bükmek (Derinlik ve Yükseklik):**
    ```math
    y_2d = (x + y) * sin(30°) - z
    ```
    *Görünüm: Sol alt çapraz. `z` değeri çıkarılarak yükseklik efekti verilir.*

### Dönüşüm Formülü 
Dönüşüm formülü (Transformation Formula), bir nesnenin konumunu, yönünü veya boyutunu değiştirmek için koordinatları üzerinde yapılan matematiksel işlemdir.
Bilgisayar grafiklerinde, bir noktayı eski halinden (x, y, z) yeni haline (x', y', z') getiren kurallar bütünüdür.
Fdf'te ise, Dönüşüm formülü, 3 boyutlu bir noktayı (x,y,z) 2 boyutlu ekran koordinatına (x', y')çeviren matematiksel işlemdir.
Genel olarak üç temel dönüşüm vardır:
1. Öteleme (Translation): Nesneyi bir yerden başka bir yere kaydırmak.
- Formül: x' = x + mesafe
2. Ölçekleme (Scaling): Nesneyi büyütmek veya küçütmek (Zoom).
- Formül: x' = x * katsayı
3. Döndürme (Rotation): Nesneyi bir eksen etrafında çevirmek.
- Formül: x' = x * cos(açı) - y * sin(açı)

FDF projesinde kullanılan standart izometrik formül şudur:
* Yeni X (Yatay Konum)
X ve Y'nin farkını al, **30°**'lik açının kosinüsü ile çarp.

```math
X_ekran = (x - y) * cos(0.523599)
```

* Yeni Y (Dikey Konum)
X ve Y'nin toplamını al, **30°**'lik açının sinüsü ile çarp ve yüksekliği (**z**) çıkar.

```math
Y_ekran = (x + y) * sin(0.523599) - z
```

> **Not:** `0.523599` radyan, **30 dereceye** eşittir.

----

## Basit Bir Örnek

Elimizde 3D uzayda şöyle bir nokta olsun: **`(2, 1, 5)`**
*(x=2, y=1, z=5)*

İzometrik hesaplama şöyle yapılır:

```text
x_new = (2 - 1) * 0.866  =  0.866
y_new = (2 + 1) * 0.5 - 5 = -3.5