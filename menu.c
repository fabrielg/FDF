/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:33:17 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/24 15:55:52 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "./libft/libft.h"

#define TEXT_COLOR 0xEAEAEA

void	put_str(t_fdf *fdf, int x, int y, char *str)
{
	mlx_string_put(fdf->mlx, fdf->window, x, y, TEXT_COLOR, str);
}

static void	display_controls(t_fdf *fdf)
{
	put_str(fdf, 30, 50, "=== FDF CONTROLS ===");
	put_str(fdf, 30, 80, "ESC: QUIT");
	put_str(fdf, 30, 100, "+/-: Z DIVISOR");
	put_str(fdf, 30, 120, "SCROLL: ZOOM IN/OUT");
	put_str(fdf, 30, 140, "P/I: PARALLEL/ISOMETRIC");
}

static void	display_infos(t_fdf *fdf)
{
	char	*z_divisor;
	char	*scale;

	z_divisor = ft_itoa(fdf->projection.z_divisor * 100);
	scale = ft_itoa(fdf->projection.scale);
	put_str(fdf, 30, 170, "=== FDF INFOS ===");
	put_str(fdf, 30, 200, "Z DIVISOR : ");
	if (z_divisor)
	{
		put_str(fdf, 110, 200, z_divisor);
		free(z_divisor);
	}
	else
		put_str(fdf, 110, 200, "ERROR");
	put_str(fdf, 30, 220, "SCALE : ");
	if (scale)
	{
		put_str(fdf, 110, 220, scale);
		free(scale);
	}
	else
		put_str(fdf, 110, 220, "ERROR");
}

void	display_menu(t_fdf *fdf)
{
	display_controls(fdf);
	display_infos(fdf);
}
