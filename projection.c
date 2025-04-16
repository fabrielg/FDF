/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:05:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/16 17:11:28 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
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
	if (proj_width == 0 || proj_height == 0)
	{
		ft_putendl_fd("Error: Projection width or height is zero", 2);
		return (0);
	}
	scale_x = (fdf->img.width * margin) / proj_width;
	scale_y = (fdf->img.height * margin) / proj_height;
	fdf->img.default_scale = ft_min(scale_x, scale_y);
	fdf->img.offsets[X] = (fdf->img.width - proj_width
			* fdf->img.default_scale)
		/ 2 - fdf->min_points[X]->v.axis[X] * fdf->img.default_scale;
	fdf->img.offsets[Y] = (fdf->img.height - proj_height
			* fdf->img.default_scale)
		/ 2 - fdf->min_points[Y]->v.axis[Y] * fdf->img.default_scale;
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
