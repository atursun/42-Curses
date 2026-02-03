
# FDF SUBJECT

**Introduction**

Bir arazinin (landscape) 3 boyutlu (3D) olarak temsil edilmesi, modern haritalandırmanın kritik bir unsurudur.
Örneğin, günümüzdeki uzay keşifleri bağlamında, Mars’ın 3 boyutlu bir temsilinin bulunması, onun keşfi için bir ön koşuldur.

Bir başka örnek olarak, tektonik hareketlerin yoğun olduğu bir bölgenin farklı 3D temsillerinin karşılaştırılması, bu olguları ve zaman içindeki gelişimlerini daha iyi anlamanızı sağlar ve bunun sonucunda daha hazırlıklı olmanıza yardımcı olur.

Bugün ise sıra sizde. Hayali ya da gerçek olsun, etkileyici 3 boyutlu manzaralar/azariler (landscape) modellemeniz beklenmektedir.

**FDF**, Fransızca *“fil de fer”* ifadesinin kısaltmasıdır ve **“tel kafes (wireframe) model”** anlamına gelir.


- Landscape (Arazi):
    landscape, bir bölgenin yeryüzü şekillerini ifade eder: Dağlar, Tepeler, Vadiler, Düzlükler, Yükseklik farkları
    Yani haritadaki arazi yapısının tamamıdır.

- Wireframe (Tel Kafes):
    Wireframe, bir 3D modelin, Yalnızca çizgilerden oluşan, Yüzeyleri doldurulmayan, Modelin iskeletini gösteren temsil biçimidir.
    Yani, Bir objenin içini doldurmadan, sadece kenarlarını çizmek.

- Landscape Wireframe:
    Landscape wireframe, bir arazinin 3 boyutlu olarak, Yükseklik bilgileri kullanılarak, Sadece çizgiler (x, y, z noktaları arasındaki bağlantılar) ile gösterilmesidir.
    Yani, Her noktanın bir yüksekliği (z) vardır Noktalar birbirine çizgilerle bağlanır Ortaya çıkan şey, tel kafes gibi bir arazi modelidir.
    Özetle, Landscape wireframe = Yükseklik bilgisine sahip bir arazinin, yalnızca çizgiler kullanılarak 3D olarak gösterilmesi

---
**Objectives**
It’s time for you to create a basic computer graphics project!
You will use the school’s graphical library: the **MiniLibX**! This library was developed
internally and includes basic necessary tools to open a window, create images and deal
with keyboard and mouse events.
This will be an opportunity for you to become familiar with the MiniLibX library,
discover the basics of **graphics programming**, particularly how to place points in space,
connect them, and most importantly, how to view the scene from a specific viewpoint.



**mandatory part**

*description*
This project involves creating a simple wireframe model of a landscape
(Bu proje, bir manzaranın basit bir tel çerçeve modelinin oluşturulmasını içeriyor.)

Fdf;
Bu proje, çeşitli noktaları (x, y, z) doğru parçaları (kenarlar) ile birbirine bağlayarak
3D bir arazi görünümünün basit bir tel kafes (wireframe) modelini oluşturmayı amaçlamaktadır.

- relink nedir


## Rendering (Olşuturma)
Programınız modeli **izometrik projeksiyon** ile göstermelidir.
Arazinin (landscape) koordinatları, programınıza komut satırı parametresi olarak verilen bir .fdf dosyasında saklanır.
$>cat 42.fdf
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0  0  0 10 10 10 10 10  0  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10  0  0 10 10  0  0  0  0  0  0  0 10 10  0  0
0  0 10 10 10 10 10 10  0  0  0  0 10 10 10 10  0  0  0
0  0  0 10 10 10 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10  0  0  0  0  0  0
0  0  0  0  0  0 10 10  0  0  0 10 10 10 10 10 10  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
$>
Programı çalıştırmak için:
- **$>./fdf 42.fdf** -> çıktı olarak bir görüntü oluşturması gerekiyor

Her sayı uzaydaki bir noktayı temsil eder:
- Yatay konum, noktanın apsisine (x) karşılık gelir.
- Dikey konum, noktanın ordinatına (y) karşılık gelir.
- Değer, noktanın yüksekliğini (z / rakım) ifade eder.

## Graphic management (Grafik Yönetimi)
- Programınız, görüntüyü bir pencere içinde göstermelidir.
- Pencere yönetimi akıcı olmalıdır (örneğin başka bir pencereye geçerken, pencereyi küçültürken vb.).
- ESC tuşuna basıldığında, pencere kapanmalı ve program temiz bir şekilde sonlandırılmalıdır.
- Pencerenin çerçevesindeki kapatma (X) butonuna tıklandığında, pencere kapanmalı ve program temiz bir şekilde sonlandırılmalıdır.
- MiniLibX kütüphanesinin image (görüntü) yapılarının kullanılması zorunludur.
