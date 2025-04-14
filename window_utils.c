/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:33:17 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/07 16:51:06 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"

#define WINDOW_BG_COLOR 0x16151f

int	init_window(t_fdf *fdf)
{
	if (!fdf)
		return (0);
	fdf->window_width = WINDOW_WIDTH;
	fdf->window_height = WINDOW_HEIGHT;
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	fdf->img.width = WINDOW_WIDTH / 1.5;
	fdf->img.height = WINDOW_HEIGHT;
	fdf->img.img = mlx_new_image(fdf->mlx, fdf->img.width, fdf->img.height);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, \
		&fdf->img.line_length, &fdf->img.endian);
	fdf->img.bg_color = WINDOW_BG_COLOR;
	fdf->img.default_scale = 1.0;
	return (1);
}

int	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->window);
	exit(0);
	return (1);
}
