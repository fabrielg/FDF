/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/07 17:54:45 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "matrix.h"
#include <math.h>

static int	handle_key_pressed(int keycode, t_fdf *fdf)
{
	if (keycode == 65307)
		close_window(fdf);
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
	close(fd);
	draw_map(fdf.projected_map, fdf.nb_rows, fdf.nb_cols, &fdf.img);
	mlx_put_image_to_window(fdf.mlx, fdf.window, fdf.img.img, 0, 0);
	mlx_hook(fdf.window, 2, 1L << 0, handle_key_pressed, &fdf);
	mlx_hook(fdf.window, 17, 0, close_window, &fdf);
	mlx_loop(fdf.mlx);
	close_window(&fdf);
	return (0);
}
