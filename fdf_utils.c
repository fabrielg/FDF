/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:04:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 21:53:24 by gfrancoi         ###   ########.fr       */
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

void	set_scale(t_map *map)
{
	t_vector2	scales;

	scales.axis[X] = (float)WIN_WIDTH
		/ (float)(map->limits[1].axis[X] + 1 - map->limits[0].axis[X]);
	scales.axis[Y] = (float)WIN_HEIGHT
		/ (float)(map->limits[1].axis[Y] + 1 - map->limits[0].axis[Y]);
	if (scales.axis[X] < scales.axis[Y])
		map->scale = scales.axis[X] * 1.0f;
	else
		map->scale = scales.axis[Y] * 1.0f;
	map->scale_min = map->scale * 0.5f;
	map->scale_max = map->scale * 5.0f;
}

void	set_offsets(t_map *map)
{
	t_vector2	proj_center;
	t_vector2	win_center;

	proj_center.axis[X] = ((map->limits[0].axis[X] + map->limits[1].axis[X])
			* map->scale / 2);
	proj_center.axis[Y] = ((map->limits[0].axis[Y] + map->limits[1].axis[Y])
			* map->scale / 2);
	win_center.axis[X] = WIN_WIDTH / 2;
	win_center.axis[Y] = WIN_HEIGHT / 2;
	map->offsets.axis[X] = win_center.axis[X] - proj_center.axis[X];
	map->offsets.axis[Y] = win_center.axis[Y] - proj_center.axis[Y];
}
