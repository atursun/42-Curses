/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:23:48 by atursun           #+#    #+#             */
/*   Updated: 2026/02/01 13:15:58 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_esc(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		free_all(fdf);
	return (0);
}

void	render_line(t_fdf *fdf, t_point start, t_point end)
{
	t_line line;

	line.start = start;
	line.end = end;
	if (!start.has_color && !end.has_color)
	{
		line.start.color = WHITE;
		line.end.color = WHITE;
	}
	isometric(&line);

	// scale
	line.start.x *= fdf->cam->scale_factor;
	line.start.y *= fdf->cam->scale_factor;
	line.end.x *= fdf->cam->scale_factor;
	line.end.y *= fdf->cam->scale_factor;

	// translate
	line.start.x += fdf->cam->move_x;
	line.start.y += fdf->cam->move_y;
	line.end.x += fdf->cam->move_x;
	line.end.y += fdf->cam->move_y;

	bresenham(fdf, line.start, line.end);
}

void	render_image(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->maxY)
	{
		x = 0;
		while (x < fdf->map->maxX)
		{
			if (x < fdf->map->maxX - 1)
				render_line(fdf, fdf->map->coord[x][y], \
					fdf->map->coord[x + 1][y]);
			if (y < fdf->map->maxY - 1)
				render_line(fdf, fdf->map->coord[x][y], \
					fdf->map->coord[x][y + 1]);
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
	render_image(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image->image, 0, 0);
	mlx_string_put(fdf->mlx, fdf->win, 50, 100, 0XC70839, "PRESS 'ESC' TO CLOSE");
	mlx_key_hook(fdf->win, handle_esc, fdf);
	mlx_hook(fdf->win, 17, 0, &free_all, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}

// pylone.fdf haritası çalışmıyıor çünkü 0 eşit değil galiba

/*
Proje akış şeması

1. Map parsing: .map dosyası -> satır satır oku -> sütun sayısını kontrol et -> 3D noktaları oluştur (x, y, z, color) -> haritayı merkeze al

*/


/* README.md FDF
Bu proje, 3D .fdf dosyayı/haritayı 2D ortamda/ekranda izometrik projeksiyon 
ile ekranda tel kafes (wireframe) şeklinde çizmek.

GENEL
- map x
- izometrik x
- wireframe x
- graphic programming

KOD MANTIĞI
- 


*/