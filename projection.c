/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:00:34 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/02 18:41:22 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"
#include <stdio.h>

static t_vector2	projection_iso(t_map *map, t_vector3 v3)
{
	t_vector2	v2;
	float		angle;

	angle = 0.523599;
	v2.axis[X] = (int)((v3.axis[X] - v3.axis[Y]) * cosf(angle)
			* map->scale + map->offsets.axis[X]);
	v2.axis[Y] = (int)((v3.axis[X] + v3.axis[Y]) * sinf(angle)
			* map->scale - v3.axis[Z] * map->scale * map->z_coeff
			+ map->offsets.axis[Y]);
	return (v2);
}

void	apply_projection(t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
			map->proj[y][x].v = projection_iso(map, map->points[y][x].v);
	}
}
