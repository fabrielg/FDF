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
#include "./libft/libft.h"

#define WINDOW_BG_COLOR 0x16151f

static void	init_projection_img(t_fdf *fdf)
{
	fdf->projection.width = WINDOW_WIDTH / 5 * 4;
	fdf->projection.height = WINDOW_HEIGHT;
	fdf->projection.img = mlx_new_image(fdf->mlx,
			fdf->projection.width,
			fdf->projection.height);
	fdf->projection.addr = mlx_get_data_addr(fdf->projection.img,
			&fdf->projection.bits_per_pixel,
			&fdf->projection.line_length,
			&fdf->projection.endian);
	fdf->projection.bg_color = WINDOW_BG_COLOR;
	fdf->projection.default_scale = 1.0;
	ft_super_memset(fdf->projection.addr,
		&fdf->projection.bg_color,
		(fdf->projection.height) * (fdf->projection.width),
		sizeof(int));
}

static void	init_menu(t_fdf *fdf)
{
	fdf->menu.width = WINDOW_WIDTH / 5;
	fdf->menu.height = WINDOW_HEIGHT;
	fdf->menu.img = mlx_new_image(fdf->mlx,
			fdf->menu.width,
			fdf->menu.height);
	fdf->menu.addr = mlx_get_data_addr(fdf->menu.img,
			&fdf->menu.bits_per_pixel,
			&fdf->menu.line_length,
			&fdf->menu.endian);
	fdf->menu.bg_color = 0x080808;
	fdf->menu.default_scale = 1.0;
	fdf->projection.default_scale = 1.0;
	ft_super_memset(fdf->menu.addr,
		&fdf->menu.bg_color,
		(fdf->menu.height) * (fdf->menu.width),
		sizeof(int));
}

int	init_window(t_fdf *fdf)
{
	if (!fdf)
		return (0);
	fdf->window_width = WINDOW_WIDTH;
	fdf->window_height = WINDOW_HEIGHT;
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	init_projection_img(fdf);
	init_menu(fdf);
	return (1);
}

static void	free_mlx(void *mlx, void *window, void *projection, void *menu)
{
	if (!mlx)
		return ;
	if (projection)
		mlx_destroy_image(mlx, projection);
	if (menu)
		mlx_destroy_image(mlx, menu);
	if (window)
		mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	if (mlx)
		free(mlx);
}

int	close_window(t_fdf *fdf)
{
	if (!fdf)
		return (0);
	free_mlx(fdf->mlx, fdf->window, fdf->projection.img, fdf->menu.img);
	free_fdf(fdf);
	exit(0);
	return (1);
}
