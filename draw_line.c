/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:45:35 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 16:02:38 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "fdf.h"

static long	ft_abs(int x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

static void	update_point(t_vector2 *p0, int deltas[2], int steps[2], int *err)
{
	int	err2;

	err2 = 2 * (*err);
	if (err2 >= deltas[Y])
	{
		*err += deltas[Y];
		p0->axis[X] += steps[X];
	}
	if (err2 <= deltas[X])
	{
		*err += deltas[X];
		p0->axis[Y] += steps[Y];
	}
}

void	draw_line(t_vector2 point0, t_vector2 point1, t_data *img, int color)
{
	int	deltas[2];
	int	steps[2];
	int	err;
	int	err2;

	deltas[X] = ft_abs(point1.axis[X] - point0.axis[X]);
	steps[X] = (point0.axis[X] < point1.axis[X]) * 2 - 1;
	deltas[Y] = -ft_abs(point1.axis[Y] - point0.axis[Y]);
	steps[Y] = (point0.axis[Y] < point1.axis[Y]) * 2 - 1;
	err = deltas[X] + deltas[Y];
	while (1)
	{
		put_pixel(img, point0.axis[X], point0.axis[Y], color);
		if (point0.axis[X] == point1.axis[X]
			&& point0.axis[Y] == point1.axis[Y])
			break ;
		update_point(&point0, deltas, steps, &err);
	}
}
