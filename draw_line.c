/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:45:35 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 20:58:27 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "fdf.h"

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

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || data->width < x || y < 0 || data->height < y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_vector2 p0, t_vector2 p1, t_img_data *img, int color)
{
	int	deltas[2];
	int	steps[2];
	int	err;

	deltas[X] = ft_abs(p1.axis[X] - p0.axis[X]);
	steps[X] = (p0.axis[X] < p1.axis[X]) * 2 - 1;
	deltas[Y] = -ft_abs(p1.axis[Y] - p0.axis[Y]);
	steps[Y] = (p0.axis[Y] < p1.axis[Y]) * 2 - 1;
	err = deltas[X] + deltas[Y];
	while (1)
	{
		put_pixel(img, p0.axis[X], p0.axis[Y], color);
		if (p0.axis[X] == p1.axis[X]
			&& p0.axis[Y] == p1.axis[Y])
			break ;
		update_point(&p0, deltas, steps, &err);
	}
}
