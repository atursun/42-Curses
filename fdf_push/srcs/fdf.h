/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:01:38 by atursun           #+#    #+#             */
/*   Updated: 2026/02/03 15:49:50 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../libs/mlx_linux/mlx.h"
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
	t_line	*line;
}	t_image;

typedef struct s_cam
{
	float	scale_factor;
	float	move_x;
	float	move_y;
}	t_cam;

typedef struct s_map_lines
{
	char	**line;
	int		count_line;
}	t_map_lines;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	int			winx;
	int			winy;
	t_image		*image;
	t_cam		*cam;
	t_map		*map;
	t_map_lines	map_line;
}	t_fdf;

# define WIDTH				2000
# define HEIGHT				1800
# define THIRTY_DEGREE_ANG  0.52359877

int		free_all(t_fdf *fdf);
void	init_mlx_image_cam(t_fdf *fdf);
t_map	*parse_map(char *file, t_fdf *fdf);
t_point	**allocate_coordinates(int width, int depth);
void	bresenham(t_fdf *fdf, t_point start, t_point end);

#endif