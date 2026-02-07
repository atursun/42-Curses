/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:56 by atursun           #+#    #+#             */
/*   Updated: 2026/02/07 13:53:47 by atursun          ###   ########.fr       */
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
	if (image->endian == 1)	// big endian (sonuç olarak 0XAARRGGBB)
	{
		// Rengin ALPHA bileşenini alıp buffer’ın ilk byte’ına yazıyor.
		image->buffer[pixel + 0] = (color >> 24);	// 0x000000AA (sonuç: Sadece Alpha byte’ını elde etmiş oluruz.)
		image->buffer[pixel + 1] = (color >> 16);
		image->buffer[pixel + 2] = (color >> 8);
		image->buffer[pixel + 3] = (color);
	}
	else if (image->endian == 0)  // little endian	(sonuç olarak 0XBBGGRRAA)
	{
		image->buffer[pixel + 0] = (color);
		image->buffer[pixel + 1] = (color >> 8);
		image->buffer[pixel + 2] = (color >> 16);
		image->buffer[pixel + 3] = (color >> 24);
	}
}

/* DDA algoritması, iki nokta arasındaki çizgiyi küçük küçük adımlara bölerek çizer.
* 

- start noktasından end noktasına kadar piksel piksel bir çizgi oluştur

end.x ve end.y değerlerini kullanmıyor gibi görebilirsin ama 
şurası önemli: (yani zaten burada kullanmışız yani uzunluğunu ve yönünü almışız)
	- dx = end.x - start.x;
	- dy = end.y - start.y;

Bu satırlar şunu yapıyor:
“start noktasından end noktasına gitmek için
X’te ne kadar ilerlemem lazım?”
“Y’de ne kadar ilerlemem lazım?”

Bresenham algoritması mantığı:
End noktası:
👉 SADECE çizginin yönünü ve uzunluğunu hesaplamak için kullanılır.


2D gösterimi
start (2,3) - end (5, 4)

dx = 5 - 2 -> 3
dy = 4 - 3 -> 1

dx = 3 / 3
dy = 1 / 3


https://www.geogebra.org/m/VWN3g9rE
cordinate plane


*/

void	dda(t_fdf *fdf, t_point start, t_point end)
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
	/* Kaç adımda çizileceğini belirle
	Burada mantık:
		Çizgi daha çok X yönünde mi uzun?
		Yoksa Y yönünde mi?
	Hangisi daha uzunsa: O eksen kadar adım at!
	*/
	if (absolute(dx) > absolute(dy))
		steps = absolute(dx);
	else
		steps = absolute(dy);

	/* Her adımda ne kadar ilerleyeceğini hesapla
	Artık dx ve dy: “Her döngüde x ve y’yi ne kadar artıracağım?” anlamına gelir.
	*/
	dx = dx / steps;
	dy = dy / steps;
	i = 0;
	/* Döngü ile çizim
	- Başlangıç noktasından başla
	- Adım adım son noktaya doğru ilerle
	- Her adımda bir piksel çiz
	*/
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
	mlx_destroy_window(fdf->mlx, fdf->win);
	mlx_destroy_display(fdf->mlx);
	free(fdf->mlx);
	free(fdf);
	exit(0);
	return (0);
}
