/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:45:35 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 16:55:40 by gfrancoi         ###   ########.fr       */
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

static void	draw_line_h(t_point p0, t_point p1, int *deltas, t_data *img)
{
	int	direction;
	int	y;
	int	p;
	int	i;

	if (p0.x > p1.x)
		draw_line_h(p1, p0, deltas, img);
	direction = (2 * (deltas[1] < 0) - 1) * -1;
	ft_printf("Direction horizontal: %d\n", direction);
	if (deltas[0] == 0)
		return ;
	y = p0.y;
	p = 2 * deltas[1] - deltas[0];
	i = 0;
	while (i < (deltas[0] + 1))
	{
		put_pixel(img, p0.x + i, y, 0x00FF0000);
		if (p >= 0)
		{
			y += direction;
			p = p - (2 * deltas[0]);
		}
		p = p + (2 * deltas[1]);
		i++;
	}
}

static void	draw_line_v(t_point p0, t_point p1, int *deltas, t_data *img)
{
	int	direction;
	int	x;
	int	p;
	int	i;

	if (p0.y > p1.y)
		draw_line_v(p1, p0, deltas, img);
	direction = (2 * (deltas[0] < 0) - 1) * -1;
	ft_printf("Direction vertical: %d\n", direction);
	if (deltas[1] == 0)
		return ;
	x = p0.y;
	p = 2 * deltas[0] - deltas[1];
	i = 0;
	while (i < (deltas[1] + 1))
	{
		put_pixel(img, x, p0.y + i, 0x00FF0000);
		if (p >= 0)
		{
			x += direction;
			p = p - (2 * deltas[1]);
		}
		p = p + (2 * deltas[0]);
		i++;
	}
}

void	draw_line(t_point point0, t_point point1, t_data *img)
{
	int	deltas[2];

	deltas[0] = point1.x - point0.x;
	deltas[1] = point1.y - point0.y;
	if (ft_abs(point1.x - point0.x) > ft_abs(point1.y - point0.y))
		draw_line_h(point0, point1, deltas, img);
	else
		draw_line_v(point0, point1, deltas, img);
}
