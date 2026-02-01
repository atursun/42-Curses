/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 13:01:38 by atursun           #+#    #+#             */
/*   Updated: 2026/01/31 13:16:41 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
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
	int		maxX;
	int		maxY;
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
	char 	**line;
	int 	count_line;
}	t_map_lines;

typedef struct s_fdf
{
	void		*mlx;
	void		*win;
	int			winX;
	int			winY;
	t_image		*image;
	t_cam		*cam;
	t_map		*map;
	t_map_lines map_line;
}	t_fdf;			// ana struct'ım bu içinde map, cam, image vb.. yapılarım var

# define WIDTH			2000
# define HEIGHT			1500
# define MAX_PIXEL		1000
# define WHITE			0XFFFFFF
# define ANG_1			0.01745329
# define ANG_30			0.52359877
# define ANG_45			0.78539816
# define HEXADECM		"0123456789abcdef"

t_map	*parse_map(char *file, t_fdf *fdf);
int		is_file_extension_valid(char *filename);
void	init_mlx_image_cam(t_fdf *fdf);
t_point	**allocate_coordinates(int width, int depth);
int		free_all(t_fdf *fdf);
void	free_map(t_fdf *fdf);
void	render_image(t_fdf *fdf);
void	bresenham(t_fdf *fdf, t_point start, t_point end);
void	pixel_to_image(t_image *image, float x, float y, int color);
void	isometric(t_line *line);

#endif
