/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:12 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/07 12:14:12 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include <stdio.h>

int	key_press(int k, t_fdf *fdf)
{
	if (k == KEY_ESC)
		close_window(fdf);
	else if (k == KEY_RIGHT)
		fdf->map.camera[Z] -= 0.01f;
	else if (k == KEY_LEFT)
		fdf->map.camera[Z] += 0.01f;
	else if ((k == KEY_SUM || k == KEY_SUM2) && fdf->map.z_coeff < 0.5f)
		fdf->map.z_coeff += 0.001f;
	else if ((k == KEY_DIF || k == KEY_DIF2) && fdf->map.z_coeff > 0.001f)
		fdf->map.z_coeff -= 0.001f;
	else if (k == KEY_A || k == KEY_D)
		translate_x(&fdf->map, (k == KEY_D) * 5 - 5 * (k == KEY_A));
	else if (k == KEY_W || k == KEY_S)
		translate_y(&fdf->map, (k == KEY_S) * 5 - 5 * (k == KEY_W));
	else if (k == KEY_I || k == KEY_O || k == KEY_G)
		return (change_proj_function(fdf, k), 0);
	else if (k == KEY_UP || k == KEY_DOWN)
		next_color(&fdf->map, (k == KEY_UP) * 2 - 1);
	else
		return (0);
	draw_map(fdf, 0);
	return (1);
}

int	mouse_action(int button, int x, int y, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_DOWN && fdf->map.scale < fdf->map.scale_max)
		fdf->map.scale += 0.2f * fdf->map.scale / 2 ;
	else if (button == MOUSE_SCROLL_UP && fdf->map.scale > 0.5f)
		fdf->map.scale -= 0.2f * fdf->map.scale / 2 ;
	else
		return (0);
	draw_map(fdf, 0);
	return (0);
}
