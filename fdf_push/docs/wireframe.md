# 3D Nesneyi Görsel Olarak Temsil Etmek

Sanal dünyada 3 boyutlu bir nesneyi ekranda var etmenin tek bir yolu yoktur. İhtiyaca (hız, gerçekçilik, mühendislik) göre farklı yöntemler kullanılır.

Temel olarak bir 3D nesne; uzaydaki `(x, y, z)` koordinatlarına sahip **noktalar**, bu noktaları birleştiren **kenarlar** ve kenarların oluşturduğu **yüzeyler** ile tanımlanır.

---

## İşte "Sanal Dünyada Bir Nesneyi Temsil Etmenin" en temel 4 yolu:

### 1. Wireframe Model (Tel Kafes) - *Senin Projen (FDF)*
Bu, nesnenin iskeletidir. Sadece köşeler (noktalar) ve kenarlar (çizgiler) vardır.
*   **Özellik:** Yüzeyler, dokular, gölgeler yoktur. Nesnenin arkasını görebilirsin (şeffaf gibidir).
*   **Mantık:** Kürdanlarla ve hamurla bir ev maketi yapmak gibidir.
*   **Kullanım:** **FDF Projesi**, CAD çizimlerinde ilk taslak aşaması.
*   **Avantaj:** Bilgisayarı hiç yormaz, matematiksel hesaplaması en basit .olan yöntemdir.

### 2. Point Cloud (Nokta Bulutu)
Çizgi bile yoktur, sadece uzayda asılı duran binlerce veya milyonlarca nokta vardır.
*   **Özellik:** Uzaktan bakınca dolu bir nesne gibi görünür ama yaklaşırsan aradaki boşlukları fark edersin.
*   **Mantık:** Sprey boya ile havaya bir şekil çizmek veya sinek sürüsünün bir şekil oluşturması gibidir.
*   **Kullanım:** Lazer tarayıcılar (LIDAR), 3D tarama, otonom araçlar.

### 3. Polygon Mesh (Poligon Ağı) - *Oyun Dünyasının Kralı*
Noktaların arasına "yüzey" (skin) gerilerek oluşturulur. Genellikle **Üçgenlerden** (Triangles) meydana gelir.
*   **Özellik:** İçi boştur ama dışı kapalıdır (kabuk gibi). Işık ve gölge hesaplanabilir.
*   **Mantık:** Kartondan veya kağıttan (origami) şekiller yapmak gibidir.
*   **Kullanım:** Modern video oyunları (GTA, Valorant vb.) ve animasyon filmleri.

### 4. Voxel (Volumetric Pixel) - *Minecraft Mantığı*
2D dünyadaki "Piksel"in 3D dünyadaki karşılığıdır. İçi dolu küplerden oluşur.
*   **Özellik:** Parçalanabilir ve içi dolu olduğu için kesip içine bakılabilir.
*   **Mantık:** LEGO parçalarıyla bir şey inşa etmek gibidir.
*   **Kullanım:** **Minecraft**, Tıbbi görüntüleme (MR/Tomografi).

---

# Detaylı Analiz: FDF ve Wireframe

FDF projesi özelinde odaklandığımız **Wireframe** modelini biraz daha derinlemesine inceleyelim.

### Wireframe Nasıl Çalışır?
Bir 3D şekli düşün: dağ, tepe veya küp. Bu şeklin sadece:
1.  Köşelerini (noktaları)
2.  Bu köşeleri birleştiren kenarlarını (çizgiler)
çizdiğini hayal et. İşte bu **Wireframe (Tel Kafes)** modelidir.

### FDF Projesindeki Uygulaması
FDF'de süreç şöyle işler:
1.  `.fdf` harita dosyasındaki her sayı bir **Z (Yükseklik)** değeridir.
2.  Programın bu değerlerden bir **3D Grid (Izgara)** oluşturur.
3.  Loop içinde her noktayı;
    *    **Sağındaki** komşuya,
    *    **Altındaki** komşuya
    **çizgiyle bağlarsın (Line Drawing).**

Böylece ekranda dağlık arazi gibi görünen, içi boş ama şekli belli olan bir **3D tel kafes harita** oluşur.
