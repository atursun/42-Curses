/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:30 by atursun           #+#    #+#             */
/*   Updated: 2026/02/05 21:44:35 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Haritayı ekrana sığdırmak için uygun bir ölçek (scale) değeri hesaplıyor.
- Map çok büyükse → küçültüyor
- Map çok küçükse → büyütüyor
- Sonuçta ekrana düzgün sığacak bir zoom katsayısı üretiyor

ÖZETLE
Bu fonksiyon şunu yapıyor:
- Map’i ekrana tam sığdırmak için gereken X ve Y ölçeğini hesapla
- Taşmaması için küçük olan ölçeği seç
- Çok küçük çıkarsa minimum 2 yap
- Sonucu biraz küçült (÷2) ki ekrana rahat otursun
*/
float	scale_to_fit(t_map *map)
{
	float	scale_x;			// X ekseni için ölçek
	float	scale_y;			// y ekseni için ölçek
	float	scale_factor;		// Son seçilen ölçek

	scale_x = WIDTH / map->width;
	scale_y = HEIGHT / map->height;
	// Eğer büyük olanı seçersek harita ekrana sığmaz, taşar
	scale_factor = min(scale_x, scale_y);	// X ve Y’den küçük olanı seçiyor (Hangisi daha uygunsa onu seç)
	/*
	Eğer hesaplanan ölçek çok küçükse:
	Bu durumda harita: aşırı küçük ve okunmaz olur
	O yüzden diyor ki: “Scale 4’ten küçük çıkarsa, direkt 2 yap”
	Çok küçülmesine izin verme
	*/
	if (scale_factor < 4)
		return (2);
	/* Hesaplanan ölçeği biraz küçültüyor 
	Bunun sebebi genelde:
		1. Kenarlarda boşluk bırakmak
		2. Haritanın pencereye yapışmaması
	*/
	return (scale_factor / 2);
}

/* MiniLibX grafik sistemini başlatmak ve programın temel görsel bileşenlerini oluşturmak.
- Grafik penceresini açar
- Çizim yapılacak resmi (image buffer) hazırlar
- Kamera ayarlarını oluşturur


mlx_get_data_addr() parametreleri:
- image->image -> mlx_new_image() ile oluşturduğun resim objesi. “Bana bu resmin iç belleğini ver”
- &image->pixel_bits -> Her piksel kaç bit? (örneğin, 32 bit (RGBA formatı)) (pixel_bits = 32 -> Her piksel (nokta) 4 byte yer kaplıyor)
- &image->line_bytes -> Bir satır kaç byte? (Image’da bir satırın bellekte kapladığı toplam alan)
	- Genişlik 800 piksel, Her piksel 4 byte ise -> 800 * 4 = 3200 byte
- &image->endian -> Byte sıralaması nasıl? (Big endian OR Little endian)
	- normalde Piksel rengi 4 byte’tır (0x00FF00FF) Bunun bellekte hangi sırayla tutulacağını endian belirler: (RGB mi yoksa BGR mi) 
Fonksiyonun Dönüş Değeri -> Resmin bellekteki başlangıç adresi

| Değişken   | Anlamı               |
| ---------- | -------------------- |
| buffer     | Resmin ham belleği   |
| pixel_bits | Her piksel kaç bit   |
| line_bytes | Bir satır kaç byte   |
| endian     | Renk byte sıralaması |
mlx_get_data_addr: “Oluşturduğun image’ın piksellerine direkt erişebilmen için gerekli tüm teknik bilgileri verir.”


ÖZETLE, Bu fonksiyon:
- MiniLibX’i başlatır
- Bir pencere açar
- Çizim yapılacak image buffer oluşturur
- Kamera ayarlarını ayarlar
- Tüm bunları t_fdf yapısına bağlar
*/
void init_mlx_image(t_fdf *fdf)
{
	t_image	*image;

	// mlx init
	// Artık ekranda çizim yapabileceğimiz bir pencere oluştu
	fdf->mlx = mlx_init(); // MiniLibX kütüphanesini başlatır. Grafik sistemiyle iletişim kurmamızı sağlar.
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");		// Ekranda bir pencere açar ve ayarlarını veririz

	// image init
	/*
	açılan pencereye tek tek nokta yerleştirmektense önce bir buffer (image) oluşturup bütün noktaları ona yerleştirip 
	sonrasında ise bu image ekrana basarız. bunu yapmamızın nedeni image oluşturmanın daha az zahmetli olmasıdır.
	*/
	image = malloc(sizeof(t_image));
	if (!image)
		return ;
	image->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);	// verilen boyutlarda yeni bir image olştu
	// Image’ın ham bellek adresi. Artık piksellere direkt erişebiliriz. Her pikseli manuel boyayabiliriz
	image->buffer = mlx_get_data_addr(image->image, &image->pixel_bits, \
			&image->line_bytes, &image->endian);
	image->line = NULL;
	fdf->image = image;	// burada ise image'ı ana yapıya bağlıyoruz
}

/*
Harita için 2 boyutlu t_point matrisi oluşturmak.
Yani, “FDF haritasının tüm noktalarını tutacak 2 boyutlu bellek alanını oluşturur.”
*/
t_point	**allocate_coordinates(int x, int y)
{
	int		i;
	t_point	**coordinates;

	coordinates = malloc(x * sizeof(t_point *));
	if (!coordinates)
		return (NULL);
	i = 0;
	while (i < x)
	{
		coordinates[i] = malloc(y * sizeof(t_point));
		if (!coordinates[i])
			return (NULL);
		i++;
	}
	return (coordinates);
}
