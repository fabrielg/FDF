/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:04:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/23 20:35:07 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	projection_parallel(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->nb_rows)
	{
		j = 0;
		while (j < fdf->nb_cols)
		{
			fdf->projected_map[i][j].v.axis[X] = fdf->origin_map[i][j].v.axis[X]
					* fdf->projection.scale;
			fdf->projected_map[i][j].v.axis[Y] = fdf->origin_map[i][j].v.axis[Y]
					* fdf->projection.scale; 
			fdf->projected_map[i][j].color = fdf->origin_map[i][j].color;
			j++;
		}
		i++;
	}
}
