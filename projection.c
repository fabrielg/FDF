/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:05:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 20:17:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	projection_iso(t_point3 **src, t_point2 **dst, int nb_rows, int nb_cols)
{
	float			cos_a;
	float			sin_a;
	int				i;
	int				j;

	cos_a = cos(M_PI_4);
	sin_a = sin(M_PI_4);
	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (j < nb_cols)
		{
			dst[i][j].v.axis[X] = (cos_a * src[i][j].v.axis[X] - cos_a * src[i][j].v.axis[Y]) * 30;
			dst[i][j].v.axis[Y] = (sin_a * src[i][j].v.axis[X] + sin_a * src[i][j].v.axis[Y] - (src[i][j].v.axis[Z] * 0.5f)) * 30;
			dst[i][j].v.axis[X] += 500;
			dst[i][j].v.axis[Y] += 500;
			if (i == 0 && j == 0)
				dst[i][j].color = 0x0000FF;
			else
				dst[i][j].color = src[i][j].color;
			j++;
		}
		i++;
	}
	return (1);
}
