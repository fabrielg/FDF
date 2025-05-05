/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 20:20:12 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 21:12:55 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"

int	key_press(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_RIGHT)
		fdf->map.camera[Z] += 0.1f;
	else if (keycode == KEY_LEFT)
		fdf->map.camera[Z] -= 0.1f;
	else
		return (0);
	draw_map(fdf);
	return (1);
}
