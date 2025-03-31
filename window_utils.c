/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:33:17 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 20:59:48 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"

int	init_window(t_fdf *fdf)
{
	if (!fdf)
		return (0);
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	fdf->img.img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, \
		&fdf->img.line_length, &fdf->img.endian);
	return (1);
}
