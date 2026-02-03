/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:23:48 by atursun           #+#    #+#             */
/*   Updated: 2026/02/03 18:26:50 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_esc(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		free_all(fdf);
	return (0);
}

/*


# renklendirme (if (!start.has_color && !end.has_color))
Haritadan okunan noktada renk bilgisi (örneğin ,0xFF0000) yoksa, çizginin siyah (görünmez) olmasını 
engellemek için varsayılan olarak BEYAZ renk atanır.

# isometric(&line) 
(x,y,z) olan 3 boyutlu koordinat sistemi, matematiksel formüllerle (sinüs, kosinüs) 
(x,y) olan 2 boyutlu ekran düzlemine yatırılır.

# scale
Haritadaki noktalar arası mesafe varsayılan olarak 1 birimdir (örneğin x=1, x=2).
Bu ekranda sadece 1 piksel demektir ve çok küçük kalır.
scale_factor (örneğin 20) ile çarparak noktaların arasını açarız. Böylece şekil ekranda büyür (Zoom in).

# translate
Bilgisayar grafiklerinde (0,0) noktası ekranın sol üst köşesidir. Eğer öteleme yapmazsak 
harita sol üst köşeye sıkışmış olarak çizilir ve bir kısmı ekran dışında kalabilir.
move_x ve move_y değerlerini ekleyerek şekli ekranın ortasına (veya tuşlarla istediğimiz yere) kaydırırız.

# bresenham
Artık elimizde ekran koordinatlarına tam olarak oturmuş, büyütülmüş ve renklendirilmiş iki nokta var.
bresenham algoritması bu iki nokta arasındaki pikselleri tek tek hesaplayıp hafızadaki resme (image buffer) yazar.
*/
void	render_line(t_fdf *fdf, t_point start, t_point end)
{
	t_line line;
	t_point	new_start;
	t_point	new_end;

	line.start = start;
	line.end = end;

	// isometric projection	(// 3D -> 2D)
	new_start.x = (line.start.x - line.start.y) * cos(THIRTY_DEGREE_ANG);			// İzometrik projeksiyonda yeni X koordinatını hesaplar
	new_start.y = (line.start.x + line.start.y) * sin(THIRTY_DEGREE_ANG) - line.start.z;		// Yeni Y koordinatını hesaplar.
	// Sonra hesaplanan değerler orijinal yapıya geri yazılıyor:
	line.start.x = new_start.x;
	line.start.y = new_start.y;
	// aynı işlemi bitiş (end) içinde uygulanıyor
	new_end.x = (line.end.x - line.end.y) * cos(THIRTY_DEGREE_ANG);
	new_end.y = (line.end.x + line.end.y) * sin(THIRTY_DEGREE_ANG) - line.end.z;
	line.end.x = new_end.x;
	line.end.y = new_end.y;

	// scale/ölçekleme
	line.start.x *= fdf->cam->scale_factor;
	line.start.y *= fdf->cam->scale_factor;
	line.end.x *= fdf->cam->scale_factor;
	line.end.y *= fdf->cam->scale_factor;

	// translate/öteleme/move
	line.start.x += fdf->cam->move_x;
	line.start.y += fdf->cam->move_y;
	line.end.x += fdf->cam->move_x;
	line.end.y += fdf->cam->move_y;

	// Pikselleştirme (Rasterization)
	bresenham(fdf, line.start, line.end);
}

/*
Bu fonksiyon, haritadaki tüm noktaları tek tek gezer ve onları birbirine 
bağlayarak (wireframe) görüntüsünü oluşturur.
Yani, Haritadaki her bir noktayı ziyaret eder ve bu noktanın 
komşularıyla (sağındaki ve altındaki) arasındaki çizgileri çizer.
Bu iç içe döngü yapısı, (0,0) noktasından başlayıp (maxX, maxY) noktasına kadar 
haritadaki her bir noktayı tek tek ele almamızı sağlar.
*/
void	render_image(t_fdf *fdf, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)	// height (Satırları gezer (Yukarıdan aşağıya))
	{
		x = 0;
		while (x < map->width)	// width (Sütunları gezer (Soldan sağa))
		{
			if (x < map->width - 1) // bunu yapmamızın sebebi son sütüna geldiğinde ve x + 1 yaptığımızda hata alırız çünkü son saıtr bir sonraki sütün yok ki
				render_line(fdf, map->coord[x][y], map->coord[x + 1][y]);
			if (y < map->height - 1)
				render_line(fdf, map->coord[x][y], map->coord[x][y + 1]);
			x++;
		}
		y++;
	}
}

int	is_file_extension_valid(char *filename)
{
	char	*res;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	res = ft_strrchr(filename, '/');
	if (!ft_strncmp(res, "/.fdf", 5))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2 || is_file_extension_valid(argv[1]))
		exit(1);
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		return (1);
	fdf->map = parse_map(argv[1], fdf);
	if (!fdf->map) {
		free(fdf);
		return (1);
	}
	init_mlx_image_cam(fdf);
	render_image(fdf, fdf->map);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image->image, 0, 0);
	mlx_string_put(fdf->mlx, fdf->win, 50, 100, 0XC70839, "PRESS 'ESC' TO CLOSE");
	mlx_key_hook(fdf->win, handle_esc, fdf);
	mlx_hook(fdf->win, 17, 0, &free_all, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

/*
Proje akış şeması

1. Map parsing: .map dosyası -> satır satır oku -> sütun sayısını kontrol et -> 3D noktaları oluştur (x, y, z, color) -> haritayı merkeze al

*/


/* README.md FDF
Bu proje, 3D .fdf dosyayı/haritayı 2D ortamda/ekranda izometrik projeksiyon
ile ekranda tel kafes (wireframe) şeklinde/moelinde çizmek.

GENEL
- map x
- izometrik x
- wireframe x
- graphic programming

KOD MANTIĞI
- bütün kodu anla
- neden bresenham gibi
- her şeyi detayılca

*/
