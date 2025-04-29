/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:13:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 19:16:31 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include <math.h>

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

	fdf->map.projection = ft_calloc(fdf->map.cols, sizeof(t_point2 *));
	if (!fdf->map.projection)
		return (0);
	y = 0;
	while (y < fdf->map.cols)
	{
		fdf->map.projection[y] = malloc(fdf->map.rows * sizeof(t_point2));
		if (!fdf->map.projection[y])
		{
			ft_free_map((void **)fdf->map.projection, y);
			return (0);
		}
		y++;
	}
	return (1);
}

int	init_fdf(t_fdf *fdf, int fd)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	if (!parse_map(&(fdf->map), fd))
		return (0);
	if (!init_projection(fdf))
		return (0);
	init_system(fdf);
	return (1);
}

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	ft_free_map((void **)fdf->map.points, fdf->map.cols);
}
