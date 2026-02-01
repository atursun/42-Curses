/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:56 by atursun           #+#    #+#             */
/*   Updated: 2026/01/28 13:19:55 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(t_fdf *fdf, t_point start, t_point end)
{
	float	dx;
	float	dy;
	int		steps;
	int		i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = max(absolute(dx), absolute(dy));
	dx /= steps;
	dy /= steps;
	i = 0;
	while (i <= steps)
	{
		if ((start.x > 0 && start.y > 0) && (start.x < WIDTH && start.y < HEIGHT))
			pixel_to_image(fdf->image, start.x, start.y, start.color);
		start.x += dx;
		start.y += dy;
		i++;
	}
}

void	pixel_to_image(t_image *image, float x, float y, int color)
{
	int	pixel;

	pixel = ((int)y * image->line_bytes) + ((int)x * 4);	// Bellekteki adresi hesaplar.
	if (image->endian == 1)
	{
		image->buffer[pixel + 0] = (color >> 24);
		image->buffer[pixel + 1] = (color >> 16);
		image->buffer[pixel + 2] = (color >> 8);
		image->buffer[pixel + 3] = (color);
	}
	else if (image->endian == 0)
	{
		image->buffer[pixel + 0] = (color);
		image->buffer[pixel + 1] = (color >> 8);
		image->buffer[pixel + 2] = (color >> 16);
		image->buffer[pixel + 3] = (color >> 24);
	}
}

void	free_map(t_fdf *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map->maxX)		// free coordinates
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
	while (i < fdf->map->maxX)		// free coordinates
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
