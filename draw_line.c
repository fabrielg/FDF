/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:45:35 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 17:21:27 by gfrancoi         ###   ########.fr       */
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

static void	swap_points(t_point *p0, t_point *p1)
{
	t_point	temp;

	temp = *p0;
	*p0 = *p1;
	*p1 = temp;
}

static void	draw_line_h(t_point points[2], int deltas[2], t_data *img, int col)
{
	int	direction;
	int	y;
	int	p;
	int	i;

	if (points[0].axis[0] > points[1].axis[0])
		swap_points(&points[0], &points[1]);
	direction = (2 * (deltas[1] < 0) - 1) * -1;
	if (deltas[0] == 0)
		return ;
	y = points[0].axis[1];
	p = 2 * deltas[1] - deltas[0];
	i = 0;
	while (i < (deltas[0] + 1))
	{
		put_pixel(img, points[0].axis[0] + i, y, col);
		if (p >= 0)
		{
			y += direction;
			p = p - (2 * deltas[0]);
		}
		p = p + (2 * deltas[1]);
		i++;
	}
}

static void	draw_line_v(t_point points[2], int deltas[2], t_data *img, int col)
{
	int	direction;
	int	x;
	int	p;
	int	i;

	if (points[0].axis[1] > points[1].axis[1])
		swap_points(&points[0], &points[1]);
	direction = (2 * (deltas[0] < 0) - 1) * -1;
	if (deltas[1] == 0)
		return ;
	x = points[0].axis[0];
	p = 2 * deltas[0] - deltas[1];
	i = 0;
	while (i < (deltas[1] + 1))
	{
		put_pixel(img, x, points[0].axis[1] + i, col);
		if (p >= 0)
		{
			x += direction;
			p = p - (2 * deltas[1]);
		}
		p = p + (2 * deltas[0]);
		i++;
	}
}

void	draw_line(t_point point0, t_point point1, t_data *img, int color)
{
	t_point	points[2];
	int		deltas[2];

	points[0] = point0;
	points[1] = point1;
	deltas[0] = point1.axis[0] - point0.axis[0];
	deltas[1] = point1.axis[1] - point0.axis[1];
	if (ft_abs(point1.axis[0] - point0.axis[0]) > ft_abs(point1.axis[1] - point0.axis[1]))
		draw_line_h(points, deltas, img, color);
	else
		draw_line_v(points, deltas, img, color);
}
