/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:04:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/30 14:04:33 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_map_pivot(t_map *map)
{
	t_vector3	pivot;
	int			x;
	int			y;

	pivot.axis[X] = (float)(map->rows / 2);
	pivot.axis[Y] = (float)((map->size / map->rows) / 2);
	pivot.axis[Z] = 0;
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			map->points[y][x].v.axis[X] -= pivot.axis[X];
			map->points[y][x].v.axis[Y] -= pivot.axis[Y];
			map->points[y][x].v.axis[Z] -= pivot.axis[Z];
		}
	}
}

void	set_limits(t_map *map)
{
	int	x;
	int	y;

	map->limits[0].axis[X] = map->proj[0][0].v.axis[X];
	map->limits[0].axis[Y] = map->proj[0][0].v.axis[Y];
	map->limits[1].axis[X] = map->proj[0][0].v.axis[X];
	map->limits[1].axis[Y] = map->proj[0][0].v.axis[Y];
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (map->limits[0].axis[X] > map->proj[y][x].v.axis[X])
				map->limits[0].axis[X] = map->proj[y][x].v.axis[X];
			if (map->limits[0].axis[Y] > map->proj[y][x].v.axis[Y])
				map->limits[0].axis[Y] = map->proj[y][x].v.axis[Y];
			if (map->limits[1].axis[X] < map->proj[y][x].v.axis[X])
				map->limits[1].axis[X] = map->proj[y][x].v.axis[X];
			if (map->limits[1].axis[Y] < map->proj[y][x].v.axis[Y])
				map->limits[1].axis[Y] = map->proj[y][x].v.axis[Y];
		}
	}
}
