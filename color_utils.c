/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:36:33 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 19:34:18 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	rgb_to_int(t_rgb c)
{
	return ((c.r << 16) | (c.g << 8) | c.b);
}

static t_rgb	int_to_rgb(int c)
{
	t_rgb	result;

	result.r = (c >> 16) & 0xFF;
	result.g = (c >> 8) & 0xFF;
	result.b = c & 0xFF;
	return (result);
}

int	lerp_rgb(int c1, int c2, float t)
{
	t_rgb	a;
	t_rgb	b;
	t_rgb	result;

	a = int_to_rgb(c1);
	b = int_to_rgb(c2);
	result.r = a.r + (b.r - a.r) * t;
	result.g = a.g + (b.g - a.g) * t;
	result.b = a.b + (b.b - a.b) * t;
	return (rgb_to_int(result));
}
