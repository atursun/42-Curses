/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:56 by atursun           #+#    #+#             */
/*   Updated: 2026/02/03 14:23:49 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* pixel_to_image (Hafızaya Yazmak)
Verilen (x, y) koordinatına renk yazmak.

ENDIAN MANTIĞI
--------------

Bilgisayarda bir int (32 bit) şu şekilde tutulur: 0xAARRGGBB
Yani:
AA → alpha (saydamlık)
RR → kırmızı
GG → yeşil
BB → mavi

Ama bu 4 byte belleğe iki farklı şekilde yazılabilir:
1. [AA][RR][GG][BB] -> Big Endian
2. [BB][GG][RR][AA] -> Little Endian


image->buffer Nedir -> Ekrandaki tüm pikselleri tutan ham byte dizisi

Bit kaydırmamızın sebebi:
32 bitlik color değişkenini doğrudan yazamayız çünkü image buffer veriyi byte byte tutar.
Bu yüzden rengi bit kaydırmayla 4 ayrı byte’a bölüp belleğe tek tek yazıyoruz.
*/
void	pixel_to_image(t_image *image, float x, float y, int color)
{
	int	pixel;

	/* BELLEKTEKİ PİKSEL ADRESİNİ HESAPLAMA MANTIĞI
	- Her satır = line_bytes kadar yer kaplar
	- Her piksel = 4 byte (RGBA)
	-> Yani: adres = satır başlangıcı + sütun offseti
	*/
	pixel = ((int)y * image->line_bytes) + ((int)x * 4);	// Bellekte Piksel Adresini Bulma (“Bu piksel bellekte tam olarak nereye denk geliyor?” hesabını yapar.)
	
	// Endian Kontrolü (2 ihtimal var)
	// Bu bloklar, color değişkenindeki 32 bitlik rengi, bilgisayarın endian tipine uygun şekilde image buffer içine doğru byte sırasıyla yazar.
	if (image->endian == 1)	// big endian
	{
		image->buffer[pixel + 0] = (color >> 24);
		image->buffer[pixel + 1] = (color >> 16);
		image->buffer[pixel + 2] = (color >> 8);
		image->buffer[pixel + 3] = (color);
	}
	else if (image->endian == 0)  // little endian
	{
		image->buffer[pixel + 0] = (color);
		image->buffer[pixel + 1] = (color >> 8);
		image->buffer[pixel + 2] = (color >> 16);
		image->buffer[pixel + 3] = (color >> 24);
	}
}

/* Ekrana iki nokta arasında çizgi çizmek
- start noktasından end noktasına kadar piksel piksel bir çizgi oluştur
*/
void	bresenham(t_fdf *fdf, t_point start, t_point end)
{
	float	dx;
	float	dy;
	int		steps;
	int		i;

	if (!start.has_color)	// Eğer noktaya özel renk verilmemişse varsayılan olarak BEYAZ ren atandır.
		start.color = 0XFFFFFF;	// white
	// X ve Y farklarını hesaplama: Çizginin yatay ve dikey uzunluğunu bulur.
	dx = end.x - start.x;
	dy = end.y - start.y;
	// Kaç adımda ilerleyeceğini belirleme: Çizgi X yönünde mi uzuyor Yoksa Y yönünde mi. Buna bakıp: En uzun ekseni adım sayısı yapıyor.
	steps = max(absolute(dx), absolute(dy));
	// Her adımda ne kadar ilerleyeceğimizi bulma: dx ve dy artık: “Her iterasyonda ne kadar ilerleyeceğim?” anlamına gelir.
	dx /= steps;
	dy /= steps;
	i = 0;
	while (i <= steps) 	// Çizim Döngüsü (Çizgi üzerindeki tüm noktaları tek tek gezer) 
	{
		if ((start.x > 0 && start.y > 0) && (start.x < WIDTH && start.y < HEIGHT)) // Ekran Sınırı Kontrolü (Eğer nokta ekranın dışındaysa çizme!)
			pixel_to_image(fdf->image, start.x, start.y, start.color);	// “Şu (x,y) noktasına şu rengi bas”
		// Sonraki Piksele Geç
		start.x += dx;
		start.y += dy;
		i++;
	}
}

void	free_map(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map->width)		// free coordinates
		free(fdf->map->coord[i++]);
	free(fdf->map->coord);
	free(fdf->map);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf);
	exit(1);
}

int	free_all(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map->width)		// free coordinates
		free(fdf->map->coord[i++]);
	free(fdf->map->coord);
	free(fdf->map);
	mlx_destroy_image(fdf->mlx, fdf->image->image);
	free(fdf->image);
	free(fdf->cam);
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
	exit(1);
	return (0);
}
