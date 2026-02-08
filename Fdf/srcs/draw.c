/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:00:56 by atursun           #+#    #+#             */
/*   Updated: 2026/02/07 12:40:38 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_to_image(t_image *image, float x, float y, int color)
{
	int	pixel;

	pixel = ((int)y * image->line_bytes) + ((int)x * 4);
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

void	dda(t_fdf *fdf, t_point start, t_point end)
{
	float	dx;
	float	dy;
	int		steps;
	int		i;

	if (!start.has_color)
		start.color = 0XFFFFFF;
	dx = end.x - start.x;
	dy = end.y - start.y;
	if (absolute(dx) > absolute(dy))
		steps = absolute(dx);
	else
		steps = absolute(dy);
	dx = dx / steps;
	dy = dy / steps;
	i = 0;
	while (i <= steps)
	{
		if (start.x > 0 && start.y > 0 && start.x < WIDTH && start.y < HEIGHT)
			pixel_to_image(fdf->image, start.x, start.y, start.color);
		start.x += dx;
		start.y += dy;
		i++;
	}
}
