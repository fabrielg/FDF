/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 19:35:14 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "keycodes.h"
#include "fdf.h"

int	main(int ac, char **av)
{
	t_fdf	fdf;
	int		fd;

	if (ac != 2)
		return (ft_putendl_fd("Usage: ./fdf <filename>", 1), 2);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error: invalid fd", 1), 2);
	if (!init_fdf(&fdf, fd))
	{
		ft_putendl_fd("INIT FDF ERROR", 2);
		close_window(&fdf);
		return (0);
	}
	draw_map(&fdf);
	mlx_put_image_to_window(fdf.libx.mlx, fdf.libx.win, fdf.img_datas.img,
		0, 0);
	mlx_hook(fdf.libx.win, 17, 0, close_window, &fdf);
	mlx_loop(fdf.libx.mlx);
	close_window(&fdf);
	return (0);
}
