/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:05:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/23 10:13:36 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_iso_to_point(t_fdf *fdf, t_point3 *src, t_point2 *dst)
{
	float	cos_a;
	float	sin_a;
	int		x;
	int		y;
	int		z;

	cos_a = cos(M_PI_4);
	sin_a = sin(M_PI_4);
	x = src->v.axis[X];
	y = src->v.axis[Y];
	z = src->v.axis[Z] * fdf->projection.z_divisor;
	dst->v.axis[X] = (x - y) * cos_a * fdf->projection.default_scale
		+ fdf->projection.offsets[X];
	dst->v.axis[Y] = (x + y) * sin_a * fdf->projection.default_scale
		- z * fdf->projection.default_scale / 2 + fdf->projection.offsets[Y];
}

void	projection_iso(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->nb_rows)
	{
		j = 0;
		while (j < fdf->nb_cols)
		{
			apply_iso_to_point(fdf,
				&fdf->origin_map[i][j],
				&fdf->projected_map[i][j]);
			fdf->projected_map[i][j].color = fdf->origin_map[i][j].color;
			j++;
		}
		i++;
	}
}
