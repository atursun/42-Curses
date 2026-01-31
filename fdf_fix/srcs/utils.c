/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:30 by atursun           #+#    #+#             */
/*   Updated: 2026/01/31 13:34:39 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	scale_to_fit(t_map *map)
{
	float	scale_x;
	float	scale_y;
	float	scale_factor;

	scale_x = WIDTH / map->maxX;
	scale_y = HEIGHT / map->maxY;
	scale_factor = min(scale_x, scale_y);
	if (scale_factor < 4)
		return (2);
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
void init_mlx_image_cam(t_fdf	*fdf)
{
	t_image	*image;
	t_cam	*cam;

	// mlx init
	// Artık ekranda çizim yapabileceğimiz bir pencere oluştu
	fdf->mlx = mlx_init(); // MiniLibX kütüphanesini başlatır. Grafik sistemiyle iletişim kurmamızı sağlar.
	fdf->winX = WIDTH;
	fdf->winY = HEIGHT;
	fdf->win = mlx_new_window(fdf->mlx, fdf->winX, fdf->winY, "FDF");		// Ekranda bir pencere açar ve ayarlarını veririz

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

	// camera init
	/*
	Ekrandaki konum, Kaydırma (move) bilgileri tarzı bilgileri tutar
	*/
	cam = malloc(sizeof(t_cam));
	if (!cam)
		return ;
	cam->scale_factor = scale_to_fit(fdf->map);	// Haritayı ekrana sığdıracak uygun zoom değerini hesaplar (Çok büyük bir map ise → küçültür, Çok küçük ise → büyütür)
	// Kamerayı ekranın ortasına koyar (Çizimler pencerenin tam ortasında başlasın diye)
	cam->move_x = WIDTH / 2;
	cam->move_y = HEIGHT / 2;
	fdf->cam = cam;
}

void	isometric(t_line *line)
{
	t_point	new_start;
	t_point	new_end;

	new_start.x = (line->start.x - line->start.y) * cos(ANG_30);
	new_start.y = (line->start.x + line->start.y) * sin(ANG_30) - line->start.z;
	line->start.x = new_start.x;
	line->start.y = new_start.y;
	new_end.x = (line->end.x - line->end.y) * cos(ANG_30);
	new_end.y = (line->end.x + line->end.y) * sin(ANG_30) - line->end.z;
	line->end.x = new_end.x;
	line->end.y = new_end.y;
}

/*
Harita için 2 boyutlu t_point matrisi oluşturmak.
Yani, “FDF haritasının tüm noktalarını tutacak 2 boyutlu bellek alanını oluşturur.”
*/
t_point	**allocate_coordinates(int width, int depth)
{
	int		i;
	t_point	**coordinates;

	coordinates = malloc(width * sizeof(t_point *));
	if (!coordinates)
		return (NULL);
	i = 0;
	while (i < width)
	{
		coordinates[i] = malloc(depth * sizeof(t_point));
		if (!coordinates[i])
			return (NULL);
		i++;
	}
	return (coordinates);
}
