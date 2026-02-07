/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:23:48 by atursun           #+#    #+#             */
/*   Updated: 2026/02/07 12:40:51 by atursun          ###   ########.fr       */
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
	t_line	line;
	t_point	new_end;
	t_point	new_start;

	line.start = start;
	line.end = end;
	new_start.x = (line.start.x - line.start.y) * cos(THIRTY_DEGREE_ANG);
	new_start.y = (line.start.x + line.start.y)
		* sin(THIRTY_DEGREE_ANG) - line.start.z;
	line.start.x = new_start.x;
	line.start.y = new_start.y;
	new_end.x = (line.end.x - line.end.y) * cos(THIRTY_DEGREE_ANG);
	new_end.y = (line.end.x + line.end.y) * sin(THIRTY_DEGREE_ANG) - line.end.z;
	line.end.x = new_end.x;
	line.end.y = new_end.y;
	line.start.x *= fdf->scale_factor;
	line.start.y *= fdf->scale_factor;
	line.end.x *= fdf->scale_factor;
	line.end.y *= fdf->scale_factor;
	line.start.x += WIDTH / 2;
	line.start.y += HEIGHT / 2;
	line.end.x += WIDTH / 2;
	line.end.y += HEIGHT / 2;
	dda(fdf, line.start, line.end);
}

void	render_image(t_fdf *fdf, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	fdf->scale_factor = scale_to_fit(fdf->map);
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
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
	char	*name;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	res = ft_strrchr(filename, '.');
	if (res == NULL)
		return (1);
	name = ft_strrchr(filename, '/');
	if (name)
		name++;
	else
		name = filename;
	if (name[0] == '.')
		return (1);
	if (ft_strncmp(res, ".fdf", 5))
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
	if (!fdf->map)
	{
		free(fdf);
		return (1);
	}
	init_mlx_image(fdf);
	render_image(fdf, fdf->map);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->image->image, 0, 0);
	mlx_string_put(fdf->mlx, fdf->win, 50, 100, 0XC70839,
		"PRESS 'ESC' TO CLOSE");
	mlx_key_hook(fdf->win, handle_esc, fdf);
	mlx_hook(fdf->win, 17, 0, &free_all, fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
