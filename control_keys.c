/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:12 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 21:28:50 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

int	key_press(int k, t_fdf *fdf)
{
	if (k == KEY_ESC)
		close_window(fdf);
	else if (k == KEY_RIGHT)
		fdf->map.camera[Z] += 0.1f;
	else if (k == KEY_LEFT)
		fdf->map.camera[Z] -= 0.1f;
	else if ((k == KEY_SUM || k == KEY_SUM2) && fdf->map.z_coeff < 0.5f)
		fdf->map.z_coeff += 0.01f;
	else if ((k == KEY_DIF || k == KEY_DIF2) && fdf->map.z_coeff > 0.01f)
		fdf->map.z_coeff -= 0.01f;
	else
		return (0);
	draw_map(fdf);
	return (1);
}
