/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:05:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/23 15:45:45 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include "./libft/libft.h"

void	init_min_max_points(t_fdf *fdf)
{
	t_point2	*p;
	int			i;
	int			j;

	fdf->min_points[X] = &fdf->projected_map[0][0];
	fdf->min_points[Y] = &fdf->projected_map[0][0];
	fdf->max_points[X] = &fdf->projected_map[0][0];
	fdf->max_points[Y] = &fdf->projected_map[0][0];
	i = -1;
	while (++i < fdf->nb_rows)
	{
		j = -1;
		while (++j < fdf->nb_cols)
		{
			p = &fdf->projected_map[i][j];
			if (fdf->min_points[X]->v.axis[X] > p->v.axis[X])
				fdf->min_points[X] = p;
			if (fdf->min_points[Y]->v.axis[Y] > p->v.axis[Y])
				fdf->min_points[Y] = p;
			if (fdf->max_points[X]->v.axis[X] < p->v.axis[X])
				fdf->max_points[X] = p;
			if (fdf->max_points[Y]->v.axis[Y] < p->v.axis[Y])
				fdf->max_points[Y] = p;
		}
	}
}

int	init_scale_and_offsets(t_fdf *fdf)
{
	float	proj_width;
	float	proj_height;
	float	scale_x;
	float	scale_y;
	float	margin;

	margin = 0.9;
	proj_width = fdf->max_points[X]->v.axis[X] - fdf->min_points[X]->v.axis[X];
	proj_height = fdf->max_points[Y]->v.axis[Y] - fdf->min_points[Y]->v.axis[Y];
	if (proj_width == 0)
		proj_width = 0.01f;
	if (proj_height == 0)
		proj_height = 0.01f;
	scale_x = (fdf->projection.width * margin) / proj_width;
	scale_y = (fdf->projection.height * margin) / proj_height;
	fdf->projection.default_scale = ft_min(scale_x, scale_y);
	fdf->projection.offsets[X] = (fdf->projection.width - proj_width
			* fdf->projection.default_scale)
		/ 2 - fdf->min_points[X]->v.axis[X] * fdf->projection.default_scale;
	fdf->projection.offsets[Y] = (fdf->projection.height - proj_height
			* fdf->projection.default_scale)
		/ 2 - fdf->min_points[Y]->v.axis[Y] * fdf->projection.default_scale;
	return (1);
}

void	draw_map(t_point2 **map, int nb_rows, int nb_cols, t_img_data *img)
{
	int	i;
	int	j;

	if (!map || !(*map))
		return ;
	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (j < nb_cols)
		{
			if (j + 1 < nb_cols)
				draw_line(map[i][j].v, map[i][j + 1].v, img, map[i][j].color);
			if (i + 1 < nb_rows)
				draw_line(map[i][j].v, map[i + 1][j].v, img, map[i][j].color);
			j++;
		}
		i++;
	}
}

void	project(t_fdf *fdf)
{
	if (fdf->projection.proj == KEY_I)
		projection_iso(fdf);
	else if (fdf->projection.proj == KEY_P)
		projection_parallel(fdf);
}
