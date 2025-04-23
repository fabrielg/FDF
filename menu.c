/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:33:17 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/23 10:22:15 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "./libft/libft.h"

void	put_str(t_fdf *fdf, int x, int y, char *str)
{
	mlx_string_put(fdf->mlx, fdf->window, x, y, 0xEAEAEA, str);
}

void	display_info(t_fdf *fdf)
{
	char	*z_divisor;

	z_divisor = ft_itoa(fdf->projection.z_divisor * 100);
	put_str(fdf, 30, 50, "=== FDF CONTROLS ===");
	put_str(fdf, 30, 80, "ESC - QUIT");
	put_str(fdf, 30, 120, "=== FDF INFOS ===");
	put_str(fdf, 30, 150, "Z DIVISOR : ");
	if (z_divisor)
	{
		put_str(fdf, 110, 150, z_divisor);
		free(z_divisor);
	}
	else
		put_str(fdf, 110, 150, "ERROR");
}
