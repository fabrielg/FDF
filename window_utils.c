/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:33:17 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 18:41:15 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "./libft/libft.h"

static void	free_mlx(t_libx *libx)
{
	if (!libx->mlx)
		return ;
	if (libx->win)
		mlx_destroy_window(libx->mlx, libx->win);
	mlx_destroy_display(libx->mlx);
	if (libx->mlx)
		free(libx->mlx);
}

int	close_window(t_fdf *fdf)
{
	if (!fdf)
		return (exit(0), 0);
	if (fdf->img_datas.img)
		mlx_destroy_image(fdf->libx.mlx, fdf->img_datas.img);
	free_mlx(&fdf->libx);
	free_fdf(fdf);
	exit(0);
	return (1);
}
