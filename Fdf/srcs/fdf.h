/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:01:38 by atursun           #+#    #+#             */
/*   Updated: 2026/02/08 12:14:38 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libs/minilibx-linux/mlx.h"
# include "../libs/libft/libft.h"

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
	int		has_color;
}	t_point;

typedef struct s_map
{
	t_point	**coord;
	int		width;
	int		height;
}	t_map;

typedef struct s_line
{
	t_point	start;
	t_point	end;
}	t_line;

typedef struct s_image
{
	void	*image;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
}	t_image;

typedef struct s_map_lines
{
	char	**line;
	int		count_line;
}	t_map_lines;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	t_image		*image;
	t_map		*map;
	t_map_lines	map_line;
	float		scale_factor;
}	t_fdf;

# define WIDTH				2000
# define HEIGHT				1800
# define THIRTY_DEGREE_ANG  0.52359877

int		free_all(t_fdf *fdf);
float	scale_to_fit(t_map *map);
void	init_mlx_image(t_fdf *fdf);
t_map	*parse_map(char *file, t_fdf *fdf);
t_point	**allocate_coordinates(int x, int y);
void	dda(t_fdf *fdf, t_point start, t_point end);

#endif