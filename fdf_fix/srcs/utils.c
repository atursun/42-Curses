/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:30 by atursun           #+#    #+#             */
/*   Updated: 2026/01/30 17:37:05 by atursun          ###   ########.fr       */
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

void init_mlx_image_cam(t_fdf	*fdf)
{
	t_image	*image;
	t_cam	*cam;

	// mlx init
	fdf->mlx = mlx_init();
	fdf->winX = WIDTH;
	fdf->winY = HEIGHT;
	fdf->win = mlx_new_window(fdf->mlx, fdf->winX, fdf->winY, "FDF");	

	// image init
	image = malloc(sizeof(t_image));
	if (!image)
		return ;
	image->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	image->buffer = mlx_get_data_addr(image->image, &image->pixel_bits, \
			&image->line_bytes, &image->endian);
	image->line = NULL;
	fdf->image = image;

	// camera init
	cam = malloc(sizeof(t_cam));
	if (!cam)
		return ;
	cam->scale_factor = scale_to_fit(fdf->map);
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

void	center_map_to_origin(t_map *map, int max_y, int max_x)
{
	int	x;
	int	y;

	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			map->coord[x][y].x -= max_x / 2;
			map->coord[x][y].y -= max_y / 2;
			x++;
		}
		y++;
	}
}
