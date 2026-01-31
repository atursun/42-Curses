/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:59:28 by atursun           #+#    #+#             */
/*   Updated: 2026/01/31 15:12:06 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// Haritadaki tüm satırların aynı sayıda sütuna sahip olup olmadığını kontrol etmek
// mapte her satır aynı sayıda nokta içermeli
int	calculate_number_of_column(t_fdf *fdf)
{
	int		c_col;
	int		next_col;
	int		i;
	char 	*trimmed;
	char 	*trimmed_two;

	if (fdf->map_line.count_line == 0)
		return (0);
	trimmed_two = ft_strtrim(fdf->map_line.line[0], " \n");
	c_col = ft_len_of_word(trimmed_two, ' ');		// İlk satır referans alınır
	free(trimmed_two);
	i = 1;
	while (i < fdf->map_line.count_line)
	{
		trimmed = ft_strtrim(fdf->map_line.line[i], " \n");
		next_col = ft_len_of_word(trimmed, ' ');
		if (c_col != next_col)	// Uyuşmazsa → harita bozuk
			return (0);
		i++;
		free(trimmed);
	}
	return (c_col);
}

/*
verilen string formatı (42,0xFF0000 || 5) bunları t_point yapısına yerleştiriyor

---
Bu kod noktaları dosyadaki doğal haliyle yerleştirir. Koordinatlar (0,0)’dan başlar ve hep pozitif yönde büyür. 
Harita ekranın köşesinde kalır ve merkezlenmiş olmaz.
- map->coord[x][y].x = x;
- map->coord[x][y].y = y;

Bu kod ise noktaları oluştururken aynı anda merkeze kaydırır. X ve Y değerlerinden haritanın yarısını çıkararak 
koordinatları negatif–pozitif aralığa taşır ve haritayı doğrudan (0,0) merkezine yerleştirir.
- map->coord[x][y].x = x - map->maxX / 2;
- map->coord[x][y].y = y - map->maxY / 2;

Haritayı koordinat sisteminin MERKEZİNE (ORJİN) taşımak.
- Dosyadan okunan harita koordinatları varsayılan olarak (0,0) köşesinden başlar.
- Bu durum haritanın ekranın köşesinde kalmasına ve dönüşlerin dengesiz olmasına yol açar.
- Koordinatları merkeze kaydırmak, tüm noktaları (0,0) etrafında simetrik hale getirir.
- Böylece zoom, döndürme ve çizim işlemleri matematiksel olarak doğru ve düzgün çalışır.
---



*/
void	place_the_point(char *point, t_map *map, int x, int y)
{
	char	**vertex;	// Vertex, 3D (veya 2D) uzayda bir şeklin tek bir köşe/noktasıdır. FDF’de 2,0xff gibi bir ifade, yüksekliği ve rengi olan bir vertexi temsil eder.

	// map->coord[x][y].x = x;
	// map->coord[x][y].y = y;
	map->coord[x][y].x = x - map->maxX / 2;
	map->coord[x][y].y = y - map->maxY / 2;
	if (ft_strchr(point, ','))	// renk varmı kontrol edilir
	{
		vertex = ft_split(point, ',');
		map->coord[x][y].z = ft_atoi(vertex[0]);
		map->coord[x][y].color = ft_atoi_base(vertex[1], HEXADECM);
		map->coord[x][y].has_color = 1;
		ft_free(vertex);
	}
	else	// eğer renk yoksa sadece yükselik değeri alınır ve ilerleyen süreçlerde color değeri atanır.
	{
		map->coord[x][y].z = ft_atoi(point);
		map->coord[x][y].has_color = 0;
	}
}

/*
tek tek her noktayı coord'a ekliyorum 
*/
void	get_points(t_fdf *fdf)
{
	char	**split;
	int		x;
	int		y;

	y = 0;	// satır sayısı (height)
	while (y < fdf->map_line.count_line)
	{
		split = ft_split(fdf->map_line.line[y], ' ');
		if (!split) 
			return ;
		x = 0;	// sütün sayısı (width)
		while (split[x])
		{
			if (x < fdf->map->maxX)
				place_the_point(split[x], fdf->map, x, y);
			free(split[x]);
			x++;
		}
		free(split);
		y++;
	}
}

/*
bu fonksiyon açıklan dosyanın fd sini alıyor ve get_next_line ile dosyayı satır satır okuyor
okudğu her satırı ise struct'e ekliyor
bunu yapmamın nedeni başka fonksiyonlarda tekrar tekrar açmamak

*/
int read_map(int fd, t_fdf *fdf) {
	fdf->map_line.count_line = 0;
	fdf->map_line.line = malloc(sizeof(char *) * 10000);	// maximum 10000 satır gibi düşün
	if (!fdf->map_line.line)
		return (0);
	while (fdf->map_line.count_line < 10000) {
		fdf->map_line.line[fdf->map_line.count_line] = get_next_line(fd);
		if (fdf->map_line.line[fdf->map_line.count_line] == NULL)
			break ;
		fdf->map_line.count_line++;
	}
	close(fd);
	fdf->map_line.line[fdf->map_line.count_line] = NULL;
	return (fdf->map_line.count_line);
}

/*
Bu fonksiyon;
Verilen map dosyasını açıyor, satırları tek tek okuyor, sütun/satır sayısını buluyor, noktaları oluşturuyor ve haritayı merkeze alıyor
*/
t_map	*parse_map(char *file, t_fdf *fdf)
{
	int		fd;

	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd  == -1) {
		return (NULL);
	}
	if (read_map(fd, fdf) == 0) {
		free(fdf->map);
		free(fdf->map_line.line);
		close(fd);
		return (NULL);
	}
	fdf->map->maxX = calculate_number_of_column(fdf);	// sütün sayısı (width) al
	fdf->map->maxY = fdf->map_line.count_line;		// satır sayısı (row) al
	if (fdf->map->maxX == 0 || fdf->map->maxY == 0) {
		return (NULL);
	}
	fdf->map->coord = allocate_coordinates(fdf->map->maxX, fdf->map->maxY);
	if (!fdf->map->coord) {
		return (NULL);
	}
	get_points(fdf);
	ft_free(fdf->map_line.line);
	return (fdf->map);
}
