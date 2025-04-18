/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:05:48 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/07 18:10:57 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include <math.h>

int	init_sphere_map(t_fdf *fdf)
{
	t_point3	**sphere_map;
	int			i;

	sphere_map = ft_calloc(fdf->nb_rows, sizeof(t_point3 *));
	if (!sphere_map)
		return (0);
	i = 0;
	while (i < fdf->nb_rows)
	{
		sphere_map[i] = ft_calloc(fdf->nb_cols, sizeof(t_point3));
		if (!sphere_map[i])
			return (0);
		i++;
	}
	fdf->sphere_map = sphere_map;
	transformation_sphere(fdf);
	return (1);
}

void	transformation_sphere(t_fdf *fdf)
{
	double	base_radius;
	double	epsilon;
	int		i;
	int		j;

	base_radius = 1.0;
	epsilon = 0.02;
	j = -1;
	while (++j < fdf->nb_rows)
	{
		i = -1;
		while (++i < fdf->nb_cols)
		{
			int		z_val = fdf->origin_map[j][i].v.axis[Z];
			double	lat = epsilon + ((double)j / (fdf->nb_rows - 1)) * (M_PI - 2 * epsilon);
			double	lon = ((double)i / (fdf->nb_cols - 1)) * 2.0 * M_PI;
			double	r = base_radius + (z_val * fdf->projection.default_scale);
			double	x = r * sin(lat) * cos(lon);
			double	y = r * sin(lat) * sin(lon);
			double	z = r * cos(lat);
			fdf->sphere_map[j][i].v.axis[X] = x;
			fdf->sphere_map[j][i].v.axis[Y] = y;
			fdf->sphere_map[j][i].v.axis[Z] = z;
			fdf->sphere_map[j][i].color = fdf->origin_map[j][i].color;
			ft_printf("Point sphere: x:%d y:%d z:%d\n",
					fdf->sphere_map[j][i].v.axis[X],
					fdf->sphere_map[j][i].v.axis[Y],
					fdf->sphere_map[j][i].v.axis[Z]);
		}
	}
}
