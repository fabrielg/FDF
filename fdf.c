/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:13:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/07 11:13:11 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <math.h>
#include <stdio.h>

#define WIN_BG_COLOR 0x16151f

static void	init_system(t_fdf *fdf)
{
	fdf->libx.mlx = mlx_init();
	fdf->libx.win = mlx_new_window(fdf->libx.mlx, WIN_WIDTH, WIN_HEIGHT,
			"FDF 42 - gfrancoi");
	fdf->img_datas.img = mlx_new_image(fdf->libx.mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->img_datas.addr = mlx_get_data_addr(fdf->img_datas.img,
			&fdf->img_datas.bits_per_pixel,
			&fdf->img_datas.line_length,
			&fdf->img_datas.endian);
}

static int	init_projection(t_fdf *fdf)
{
	int	y;
	int	x;

	fdf->map.proj = ft_calloc(fdf->map.rows, sizeof(t_point2 *));
	if (!fdf->map.proj)
		return (0);
	y = -1;
	while (++y < fdf->map.rows)
	{
		fdf->map.proj[y] = malloc(fdf->map.cols * sizeof(t_point2));
		if (!fdf->map.proj[y])
			return (0);
		x = -1;
		while (++x < fdf->map.cols)
		{
			fdf->map.proj[y][x].color = fdf->map.points[y][x].color;
			fdf->map.proj[y][x].default_color
				= fdf->map.points[y][x].default_color;
			fdf->map.proj[y][x].v.axis[X] = fdf->map.points[y][x].v.axis[X];
			fdf->map.proj[y][x].v.axis[Y] = fdf->map.points[y][x].v.axis[Y];
		}
	}
	return (1);
}

int	init_fdf(t_fdf *fdf, int fd)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	if (!parse_map(&(fdf->map), fd))
		return (0);
	fdf->map.size = fdf->map.rows * fdf->map.cols;
	center_map_pivot(&fdf->map);
	if (!init_projection(fdf))
		return (0);
	fdf->map.bg_color = WIN_BG_COLOR;
	fdf->map.scale = 1;
	fdf->map.offsets.axis[X] = 0;
	fdf->map.offsets.axis[Y] = 0;
	fdf->map.z_coeff = 0.1f;
	fdf->map.proj_function = projection_iso;
	init_system(fdf);
	apply_projection(&fdf->map);
	set_limits(&fdf->map);
	set_polar_points(&fdf->map);
	return (1);
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	ft_free_map((void **)fdf->map.points, fdf->map.rows);
	ft_free_map((void **)fdf->map.proj, fdf->map.rows);
}
