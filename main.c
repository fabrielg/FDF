/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 14:18:52 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "matrix.h"
#include "keycodes.h"
#include <math.h>

static void	window_update(t_fdf *fdf, int p)
{
	if (p)
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

static void	translate(t_fdf *fdf, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < fdf->nb_rows)
	{
		i = 0;
		while (i < fdf->nb_cols)
		{
			fdf->projected_map[j][i].v.axis[X] += x;
			fdf->projected_map[j][i].v.axis[Y] += y;
			i++;
		}
		j++;
	}
}

void	rot_y(t_vector3 *out, t_vector3 *in, float theta)
{
	float	cos;
	float	sin;

	cos = cosf(theta);
	sin = sinf(theta);
	out->axis[X] = in->axis[X] * cos - in->axis[Z] * sin;
	out->axis[Y] = in->axis[Y];
	out->axis[Z] = in->axis[X] * sin + in->axis[Z] * cos;
}

void	apply_rotation(t_fdf *fdf)
{
	t_point3	**map;
	int			x;
	int			y;

	map = fdf->copy;
	y = 0;
	ft_putendl_fd("cc", 1);
	while (y < fdf->nb_rows)
	{
		x = 0;
		while (x < fdf->nb_cols)
		{
			rot_y(&map[y][x].v, &fdf->origin_map[y][x].v, 2.0f);
			x++;
		}
		y++;
	}
}

static int	handle_key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_window(fdf);
	else if (keycode == KEY_SUM || keycode == KEY_SUM2)
	{
		fdf->projection.z_divisor += 0.05f;
		if (fdf->projection.z_divisor >= 1.05f)
			fdf->projection.z_divisor = 0.0f;
	}
	else if ((keycode == KEY_DIF || keycode == KEY_DIF2))
	{
		fdf->projection.z_divisor -= 0.05f;
		if (fdf->projection.z_divisor < 0.0f)
			fdf->projection.z_divisor = 1.0f;
	}
	else if (keycode == KEY_I || keycode == KEY_P)
		fdf->projection.proj = keycode;
	else if (KEY_LEFT <= keycode && keycode <= KEY_DOWN)
		return (translate(fdf,
			-(keycode == KEY_LEFT) * 20 + (keycode == KEY_RIGHT) * 20,
			-(keycode == KEY_UP) * 20 + (keycode == KEY_DOWN) * 20),
			window_update(fdf, 0), 0);
	else if (keycode == KEY_A)
	{
		apply_rotation(fdf);
	}
	else
		return (0);
	window_update(fdf, 1);
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
	window_update(fdf, 1);
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
