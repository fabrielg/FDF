/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 21:19:18 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "matrix.h"
#include <math.h>

void	close_window(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->window);
	exit(0);
}

int	handle_key_pressed(int keycode, t_fdf *fdf)
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
		return (0);
	}
	ft_super_memset(fdf.img.addr, &fdf.img.bg_color, (fdf.img.height) * (fdf.img.width), sizeof(int));
	close(fd);
	draw_map(fdf.projected_map, fdf.nb_rows, fdf.nb_cols, &fdf.img);
	free_map((void **)fdf.origin_map);
	free_map((void **)fdf.projected_map);
	mlx_put_image_to_window(fdf.mlx, fdf.window, fdf.img.img, 0, 0);
	mlx_hook(fdf.window, 2, 1L<<0, handle_key_pressed, &fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
