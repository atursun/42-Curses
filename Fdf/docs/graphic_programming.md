
# Graphic programming (Grafik Programlama)

Graphic programming (grafik programlama) dünyasına girerken kafayı netleştiren **temel kavramları** katman katman anlatayım.
---

## 🧱 1. Coordinate System (Koordinat Sistemi)

![Image](https://learn365project.com/wp-content/uploads/2015/08/cartesian_coordinates.png)

![Image](https://study.com/cimages/videopreview/t63ugfs1r8.jpg)

Grafikte her şey **koordinat** ile başlar.

### 2D

* `(0, 0)` → **sol üst köşe**
* `x` → sağa doğru artar
* `y` → aşağı doğru artar

```txt
(0,0) --------> x
  |
  |
  v
  y
```

### 3D

* `x` → sağ / sol
* `y` → yukarı / aşağı
* `z` → derinlik (kamera sana yaklaşıyor / uzaklaşıyor)

📌 **FDF’de:** map verisi aslında 3D’dir ama ekrana **2D olarak projekte edilir**.

---

## 🎨 2. Pixel (Piksel)

![Image](https://community.mrtrix.org/uploads/default/original/2X/c/c0d0e56e956de8cfb5f5d804f036b77e2c634672.jpeg)

![Image](https://www.researchgate.net/publication/360591547/figure/fig7/AS%3A11431281331032438%401743207996959/Optical-characteristics-of-RGB-pixel-structure-with-integrated-1D-single-pixel-PCF-that.jpg)

* Ekranın en küçük yapı taşı
* Her piksel bir **renk** tutar

```c
put_pixel(x, y, color);
```

Ama arka planda:

```c
buffer[y * line_bytes + x * 4]
```

📌 Piksel = **hafıza adresi**

---

## 🌈 3. Color Models (Renk Modelleri)

![Image](https://www.researchgate.net/profile/Egon-L-Van-Den-Broek/publication/228719004/figure/fig3/AS%3A669485950320654%401536629297405/The-RGB-color-space-visualized-as-a-cube_Q320.jpg)

![Image](https://www.researchgate.net/publication/380597911/figure/fig4/AS%3A11431281263218649%401721959791699/RGB-color-space-3D-coordinate-diagram-and-visualization-of-each-channel.png)

En yaygını: **RGB / ARGB**

### RGB

```txt
Red   Green   Blue
255   0       0     → Kırmızı
```

### ARGB (32 bit)

```txt
AA RR GG BB
```

```c
0xFF00FF00  // Yeşil
```

📌 Senin sorduğun:

> **AA BB CC DD nedir?**
> → Bunlar **kanallar** (alpha, red, green, blue)

---

## 📐 4. Primitive Shapes (Temel Şekiller)

![Image](https://media.geeksforgeeks.org/wp-content/uploads/BresenhamLine.png)

![Image](https://media.cgtrader.com/variants/nzinhsweqoyom6j7248wdhron1vf/78add9c2f02fbd73a43ffb3970be38683c5f15eff6ca849dc78c644f4ff9ce1b/Preview%201.webp)

Grafikte her şey şu temel şekillerden oluşur:

* Nokta (Point)
* Çizgi (Line)
* Üçgen (Triangle)

📌 **FDF = wireframe**
Yani:

```txt
nokta + çizgi
```

En önemli algoritma:

### 🔹 Bresenham Line Algorithm

* Float kullanmaz
* Hızlıdır
* Piksel piksel çizgi çizer

---

## 🔄 5. Transformations (Dönüşümler)

![Image](https://media.geeksforgeeks.org/wp-content/uploads/transformation-computer-graphics.png)

![Image](https://docs-be.ni.com/bundle/labview-api-ref/page/vi-lib/analysis/coordinate-llb/loc_eps_3dcartrot.gif?_LANG=enus)

Bir nesneyi:

* **Taşırsın** (Translate)
* **Döndürürsün** (Rotate)
* **Büyütür/Küçültürsün** (Scale)

### Translate

```c
x += move_x;
y += move_y;
```

### Scale

```c
x *= zoom;
y *= zoom;
```

### Rotate

```c
x' = x*cos(a) - y*sin(a)
y' = x*sin(a) + y*cos(a)
```

📌 FDF’de:

* mouse / key → transform
* sonra tekrar çizim

---

## 👁️ 6. Projection (Projeksiyon)

![Image](https://images.prismic.io/sketchplanations/ZyTZVa8jQArT0HlP_SP897-Isometricprojection.png?auto=format%2Ccompress)

![Image](https://media.geeksforgeeks.org/wp-content/uploads/20230327153754/PP.png)

3D → 2D çevirme işi.

### Isometric (FDF default)

* Paralel
* Perspektif yok
* Teknik çizim gibi

```c
x2d = (x - y) * cos(angle);
y2d = (x + y) * sin(angle) - z;
```

### Perspective

* Yakın büyük
* Uzak küçük
* Oyun / 3D engine’lerde

---

## 🖼️ 7. Framebuffer / Image Buffer

![Image](https://doc.embedded-wizard.de/images/framebuffer-concepts-1.png)

![Image](https://wentzwu.com/wp-content/uploads/2020/04/memory-layout-of-a-process.jpg)

Ekrana **doğrudan çizmezsin**:

1. Image buffer oluştur
2. Piksel piksel doldur
3. Window’a bas

```c
mlx_put_image_to_window(...)
```

📌 Bu:

* Flicker’ı önler
* Daha performanslıdır

---

## ⏱️ 8. Render Loop (Çizim Döngüsü)

![Image](https://www.gameludere.com/wp-content/uploads/2019/12/gameLoop_img01.png)

![Image](https://media.geeksforgeeks.org/wp-content/uploads/20250208123836185275/Event-Loop-in-JavaScript.jpg)

Mantık:

```txt
event → update → draw → repeat
```

MLX’te:

* key hook
* mouse hook
* loop hook

📌 ESC → exit
📌 WASD → move
📌 Scroll → zoom

---

## 🧠 9. Math (Olmazsa Olmaz)

Grafik = **matematik**

Bilmen gerekenler:

* Trigonometri (`sin cos`)
* Vektörler
* Matrix (ileride)
* Float / precision

---

## 🧩 10. Pipeline Mantığı (Büyük Resim)

![Image](https://www.researchgate.net/publication/220422248/figure/fig1/AS%3A646476724195337%401531143470958/a-simplified-graphics-pipeline.png)

![Image](https://graphicscompendium.com/intro/figures/graphics-pipeline.png)

```txt
Map data
 ↓
3D points
 ↓
Transform
 ↓
Projection
 ↓
2D points
 ↓
Lines
 ↓
Pixels
```

📌 FDF = mini graphics engine 😄

---

### İstersen şunlardan birine derin gireriz:

* 🔥 **Bresenham algoritması adım adım**
* 🎨 **Renk geçişleri (gradient)**
* 🧠 **Matrix ile rotate/scale**
* 🚀 **Mini raycasting (Wolf3D altyapısı)**

Hangisiyle devam edelim?

