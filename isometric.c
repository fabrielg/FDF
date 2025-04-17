/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:05:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/07 18:10:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	apply_iso_to_point(t_point3 *src, t_point2 *dst, int sz, int off[2])
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
	z = src->v.axis[Z] * 0.5f;
	dst->v.axis[X] = (x - y) * cos_a * sz + off[X];
	dst->v.axis[Y] = (x + y) * sin_a * sz - z * sz / 2 + off[Y];
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
			apply_iso_to_point(&fdf->origin_map[i][j],
				&fdf->projected_map[i][j],
				fdf->projection.default_scale,
				fdf->projection.offsets);
			fdf->projected_map[i][j].color = fdf->origin_map[i][j].color;
			j++;
		}
		i++;
	}
}
