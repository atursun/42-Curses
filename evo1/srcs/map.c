/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atursun <atursun@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:59:28 by atursun           #+#    #+#             */
/*   Updated: 2026/02/03 15:16:33 by atursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calculate_number_of_column(t_fdf *fdf)
{
	int		i;
	int		c_col;
	int		next_col;
	char	*trimmed;
	char	*trimmed_two;

	if (fdf->map_line.count_line == 0)
		return (0);
	trimmed_two = ft_strtrim(fdf->map_line.line[0], " \n");
	c_col = ft_len_of_word(trimmed_two, ' ');
	free(trimmed_two);
	i = 1;
	while (i < fdf->map_line.count_line)
	{
		trimmed = ft_strtrim(fdf->map_line.line[i], " \n");
		next_col = ft_len_of_word(trimmed, ' ');
		if (c_col != next_col)
			return (0);
		i++;
		free(trimmed);
	}
	return (c_col);
}

void	place_the_point(char *point, t_map *map, int x, int y)
{
	char	**vertex;

	map->coord[x][y].x = x - map->width / 2;
	map->coord[x][y].y = y - map->height / 2;
	if (ft_strchr(point, ','))
	{
		vertex = ft_split(point, ',');
		map->coord[x][y].z = ft_atoi(vertex[0]);
		map->coord[x][y].color = ft_atoi_base(vertex[1], "0123456789abcdef");
		map->coord[x][y].has_color = 1;
		ft_free(vertex);
	}
	else
	{
		map->coord[x][y].z = ft_atoi(point);
		map->coord[x][y].has_color = 0;
	}
}

void	get_points(t_fdf *fdf)
{
	char	**split;
	int		x;
	int		y;

	y = 0;
	while (y < fdf->map_line.count_line)
	{
		split = ft_split(fdf->map_line.line[y], ' ');
		if (!split)
			return ;
		x = 0;
		while (split[x] != NULL)
		{
			if (x < fdf->map->width)
				place_the_point(split[x], fdf->map, x, y);
			free(split[x]);
			x++;
		}
		free(split);
		y++;
	}
}

int	read_map(int fd, t_fdf *fdf)
{
	fdf->map_line.count_line = 0;
	fdf->map_line.line = malloc(sizeof(char *) * 10000);
	if (!fdf->map_line.line)
		return (0);
	while (fdf->map_line.count_line < 10000)
	{
		fdf->map_line.line[fdf->map_line.count_line] = get_next_line(fd);
		if (fdf->map_line.line[fdf->map_line.count_line] == NULL)
			break ;
		fdf->map_line.count_line++;
	}
	close(fd);
	fdf->map_line.line[fdf->map_line.count_line] = NULL;
	return (fdf->map_line.count_line);
}

t_map	*parse_map(char *file, t_fdf *fdf)
{
	int		fd;

	fdf->map = malloc(sizeof(t_map));
	if (!fdf->map)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (read_map(fd, fdf) == 0)
	{
		free(fdf->map);
		free(fdf->map_line.line);
		close(fd);
		return (NULL);
	}
	fdf->map->width = calculate_number_of_column(fdf);
	fdf->map->height = fdf->map_line.count_line;
	if (fdf->map->width == 0 || fdf->map->height == 0)
		return (NULL);
	fdf->map->coord = allocate_coordinates(fdf->map->width, fdf->map->height);
	if (!fdf->map->coord)
		return (NULL);
	get_points(fdf);
	ft_free(fdf->map_line.line);
	return (fdf->map);
}
