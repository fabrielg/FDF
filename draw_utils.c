/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:21:49 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/07 12:09:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include <math.h>

void	generate_background(t_fdf *fdf)
{
	ft_super_memset(fdf->img_datas.addr,
		&fdf->map.bg_color,
		WIN_HEIGHT * WIN_WIDTH,
		sizeof(int));
}

static void	fit_map(t_map *map)
{
	set_scale(map);
	set_offsets(map);
	map->camera[Z] = 0;
}

static void	get_rotation_polar(t_map *map, t_vector2f *in, t_vector2f *out)
{
	out->axis[X] = in->axis[X] + map->camera[Z];
	out->axis[Y] = in->axis[Y] + map->camera[Z];
}

void	generate_projection(t_map *map, int fit)
{
	t_vector3f	in;
	t_vector3f	out;
	t_vector2f	polar;
	int			x;
	int			y;

	if (fit)
		fit_map(map);
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			in = vector3_to_vector3f(map->points[y][x].v);
			out = in;
			rotate_z(&in, &out, map->camera[Z]);
			get_rotation_polar(map, &map->points[y][x].polar, &polar);
			if (map->globe)
				spherize(map, &out, polar);
			map->proj[y][x].v = map->proj_function(map, out);
		}
	}
	color_map(map);
}
