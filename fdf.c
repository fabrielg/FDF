/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:13:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 18:40:53 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <math.h>

static void	system_init(t_fdf *fdf)
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

int	init_fdf(t_fdf *fdf, int fd)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	if (!parse_map(&(fdf->map), fd))
		return (0);
	system_init(fdf);
	return (1);
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	ft_free_map((void **)fdf->map.points, fdf->map.cols);
}
