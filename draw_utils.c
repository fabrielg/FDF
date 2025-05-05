/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:21:49 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 20:00:27 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

void	generate_background(t_fdf *fdf)
{
	ft_super_memset(fdf->img_datas.addr,
		&fdf->map.bg_color,
		WIN_HEIGHT * WIN_WIDTH,
		sizeof(int));
}

void	generate_projection(t_map *map)
{
	t_vector3f	in;
	t_vector3f	out;
	int			x;
	int			y;

	set_scale(map);
	set_offsets(map);
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			in = vector3_to_vector3f(map->points[y][x].v);
			out = in;
			rotate_x(&in, &out, map->camera[X]);
			rotate_y(&in, &out, map->camera[Y]);
			rotate_z(&in, &out, map->camera[Z]);
			map->proj[y][x].v = projection_iso(map, out);
		}
	}
}
