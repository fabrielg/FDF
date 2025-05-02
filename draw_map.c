/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:04:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/02 20:38:34 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"

static void	wire(t_fdf *fdf)
{
	t_point2	**projection;
	int			x;
	int			y;

	y = 0;
	projection = fdf->map.proj;
	while (y < fdf->map.rows)
	{
		x = 0;
		while (x < fdf->map.cols)
		{
			if (x + 1 < fdf->map.cols)
				draw_line(projection[y][x],
					projection[y][x + 1], &fdf->img_datas);
			if (y + 1 < fdf->map.rows)
				draw_line(projection[y][x],
					projection[y + 1][x], &fdf->img_datas);
			x++;
		}	
		y++;
	}
}

static void	test(t_fdf *fdf)
{
	int	x;
	int	y;

	set_scale(&fdf->map);
	apply_rotation(&fdf->map);
	set_offsets(&fdf->map);
	apply_projection(&fdf->map);
}

void	draw_map(t_fdf *fdf)
{
	test(fdf);
	generate_background(fdf);
	wire(fdf);
	mlx_put_image_to_window(fdf->libx.mlx, fdf->libx.win, fdf->img_datas.img,
		0, 0);
}
