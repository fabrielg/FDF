/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:00:34 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 22:52:38 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"
#include <stdio.h>

void	change_proj_function(t_map *map, char proj)
{
	if (proj == 'i')
		map->proj_function = projection_iso;
	else if (proj == 'o')
		map->proj_function = projection_ortho;
}

t_vector2	projection_iso(t_map *map, t_vector3f v3f)
{
	t_vector2	v2;
	float		angle;

	angle = 0.523599;
	v2.axis[X] = (int)((v3f.axis[X] - v3f.axis[Y]) * cosf(angle)
			* map->scale + map->offsets.axis[X]);
	v2.axis[Y] = (int)((v3f.axis[X] + v3f.axis[Y]) * sinf(angle)
			* map->scale - v3f.axis[Z] * map->scale * map->z_coeff
			+ map->offsets.axis[Y]);
	return (v2);
}

t_vector2	projection_ortho(t_map *map, t_vector3f v3f)
{
	t_vector2	v2;

    v2.axis[X] = (int)(v3f.axis[X] * map->scale + map->offsets.axis[X]);
    v2.axis[Y] = (int)(v3f.axis[Y] * map->scale + map->offsets.axis[Y]);
	return (v2);
}

void	apply_projection(t_map *map)
{
	t_vector3f	v3f;
	int			x;
	int			y;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			v3f = vector3_to_vector3f(map->points[y][x].v);
			map->proj[y][x].v = map->proj_function(map, v3f);
		}
	}
}
