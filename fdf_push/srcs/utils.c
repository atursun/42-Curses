/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:30 by atursun           #+#    #+#             */
/*   Updated: 2026/02/05 21:42:58 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	scale_to_fit(t_map *map)
{
	float	scale_x;
	float	scale_y;
	float	scale_factor;

	scale_x = WIDTH / map->width;
	scale_y = HEIGHT / map->height;
	scale_factor = min(scale_x, scale_y);
	if (scale_factor < 4)
		return (2);
	return (scale_factor / 2);
}

void	init_mlx_image(t_fdf *fdf)
{
	t_image	*image;

	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	image = malloc(sizeof(t_image));
	if (!image)
		return ;
	image->image = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	image->buffer = mlx_get_data_addr(image->image, &image->pixel_bits,
			&image->line_bytes, &image->endian);
	image->line = NULL;
	fdf->image = image;
}

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

int	free_all(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map->width)
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
