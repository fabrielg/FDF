/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:33:37 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/02 20:37:18 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

/*static t_vector3f	rotate_x(t_vector3f v3, float angle)
{
	t_vector3f	result;
	float		cos;
	float		sin;

	cos = cosf(angle);
	sin = sinf(angle);
	result.axis[X] = v3.axis[X];
	result.axis[Y] = v3.axis[Y] * cos - v3.axis[Z] * sin;
	result.axis[Z] = v3.axis[Y] * sin + v3.axis[Z] * cos;
	return (result);
}*/

static t_vector3	rotate_y(t_vector3 v3, float angle)
{
	t_vector3	result;
	float		cos;
	float		sin;

	cos = cosf(angle);
	sin = sinf(angle);
	result.axis[X] = v3.axis[X] * cos - v3.axis[Z] * sin;
	result.axis[Y] = v3.axis[Y];
	result.axis[Z] = v3.axis[X] * sin + v3.axis[Z] * cos;
	return (result);
}

void	apply_rotation(t_map *map)
{
	int			x;
	int			y;

	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			map->points[y][x].v = rotate_y(map->points[y][x].v, map->camera[Y]);
		}
	}
}
