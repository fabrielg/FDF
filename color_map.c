/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:21:25 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/06 21:47:10 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include <stdio.h>

static t_vector2	get_min_max_z(t_map *map)
{
	t_vector2	min_max;
	int			x;
	int			y;

	min_max = (t_vector2){0, 0};
	y = -1;
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			if (min_max.axis[0] > map->points[y][x].v.axis[Z])
				min_max.axis[0] = map->points[y][x].v.axis[Z];
			if (min_max.axis[1] < map->points[y][x].v.axis[Z])
				min_max.axis[1] = map->points[y][x].v.axis[Z];
		}
	}
	return (min_max);
}

static void	color_p(t_point2 *p, int z, t_map_color colors, t_vector2 z_limits)
{
	float	grad;
	int		diff;

	if (!colors.bottom && !colors.ground && !colors.top)
	{
		p->color = p->default_color;
		return ;
	}
	diff = z_limits.axis[1] - z_limits.axis[0];
	printf("diff: %d\n", diff);
	if (diff == 0)
		grad = 0.5f;
	else
		grad = (float)(z - z_limits.axis[0]) / (diff);
	printf("grad: %f\n", grad);
	if (grad < 0.5f)
		p->color = lerp_rgb(colors.bottom, colors.ground, grad * 2.0f);
	else
		p->color = lerp_rgb(colors.ground, colors.top, (grad - 0.5f) * 2.f);
}

static t_map_color	new_col(unsigned int c1, unsigned int c2, unsigned int c3)
{
	t_map_color	new;

	new.bottom = c1;
	new.ground = c2;
	new.top = c3;
	return (new);
}

void	next_color(t_map *map, int step)
{
	static int	id;
	t_map_color	colors[4];

	colors[0] = new_col(0, 0, 0);
	colors[1] = new_col(0x0c62f5, 0xa17523, 0xa12323);
	colors[2] = new_col(0x0000FF, 0x33cc55, 0xc1272d);
	colors[3] = new_col(0x000000, 0xd787878, 0xFFFFFF);
	id += step;
	if (id > 3)
		id = 0;
	if (id < 0)
		id = 3;
	map->colors = colors[id];
}

void	color_map(t_map *map)
{
	t_vector2	z_limits;
	int			x;
	int			y;

	z_limits = get_min_max_z(map);
	y = -1;
	printf("colors: %p\n", &map->colors);
	while (++y < map->rows)
	{
		x = -1;
		while (++x < map->cols)
		{
			color_p(&map->proj[y][x],
				map->points[y][x].v.axis[Z],
				map->colors,
				z_limits);
		}
	}
}
