/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/23 21:19:46 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "matrix.h"
#include "keycodes.h"
#include <math.h>
#include <float.h>

static void	window_update(t_fdf *fdf)
{
	project(fdf);
	if (!fdf->projected_map)
		return ;
	ft_super_memset(fdf->projection.addr,
		&fdf->projection.bg_color,
		(fdf->projection.height) * (fdf->projection.width),
		sizeof(int));
	draw_map(fdf->projected_map, fdf->nb_rows, fdf->nb_cols, &fdf->projection);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->projection.img,
		fdf->menu.width, 0);
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->menu.img, 0, 0);
	display_menu(fdf);
}

static int	handle_key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	else if (keycode == KEY_SUM || keycode == KEY_SUM2)
	{
		fdf->projection.z_divisor += 0.05f;
		if (fdf->projection.z_divisor > 1.0f)
			fdf->projection.z_divisor = 0.1f;
	}
	else if ((keycode == KEY_DIF || keycode == KEY_DIF2)
		&& fdf->projection.z_divisor > 0.0f)
		fdf->projection.z_divisor /= 1.2f;
	else if (keycode == KEY_I || keycode == KEY_P)
		fdf->projection.proj = keycode;
	else
		return (0);
	window_update(fdf);
	return (0);
}

static int	handle_mouse_action(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_DOWN && fdf->projection.scale < 10000)
	{
		fdf->projection.scale *= 1.2;
		if (fdf->projection.scale > 10000)
			fdf->projection.scale = 10000;
	}
	else if (button == MOUSE_SCROLL_UP && fdf->projection.scale > 0.5)
		fdf->projection.scale /= 1.2;
	else
		return (0);
	window_update(fdf);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	int		fd;

	if (ac != 2)
		return (ft_putendl_fd("Usage: ./fdf <filename>", 1), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error: invalid fd", 1), 0);
	if (!init_fdf(&fdf, fd) || !fdf.origin_map || !fdf.projected_map)
	{
		ft_putendl_fd("INIT FDF ERROR", 1);
		close_window(&fdf);
		return (0);
	}
	draw_map(fdf.projected_map, fdf.nb_rows, fdf.nb_cols, &fdf.projection);
	mlx_put_image_to_window(fdf.mlx, fdf.window, fdf.projection.img,
		fdf.menu.width, 0);
	mlx_put_image_to_window(fdf.mlx, fdf.window, fdf.menu.img, 0, 0);
	display_menu(&fdf);
	mlx_hook(fdf.window, 2, 1L << 0, handle_key_pressed, &fdf);
	mlx_hook(fdf.window, 4, 1L << 2, handle_mouse_action, &fdf);
	mlx_hook(fdf.window, 17, 0, close_window, &fdf);
	mlx_loop(fdf.mlx);
	close_window(&fdf);
	return (0);
}
