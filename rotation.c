/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:33:37 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 19:45:06 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>

void	rotate_x(t_vector3f *in, t_vector3f *out, float angle)
{
	float		cos;
	float		sin;

	cos = cosf(angle);
	sin = sinf(angle);
	out->axis[X] = in->axis[X];
	out->axis[Y] = in->axis[Y] * cos - in->axis[Z] * sin;
	out->axis[Z] = in->axis[Y] * sin + in->axis[Z] * cos;
}

void	rotate_y(t_vector3f *in, t_vector3f *out, float angle)
{
	float		cos;
	float		sin;

	cos = cosf(angle);
	sin = sinf(angle);
	out->axis[X] = in->axis[X] * cos - in->axis[Z] * sin;
	out->axis[Y] = in->axis[Y];
	out->axis[Z] = in->axis[X] * sin + in->axis[Z] * cos;
}

void	rotate_z(t_vector3f *in, t_vector3f *out, float angle)
{
	float		cos;
	float		sin;

	cos = cosf(angle);
	sin = sinf(angle);
	out->axis[X] = in->axis[X] * cos - in->axis[Y] * sin;
	out->axis[Y] = in->axis[X] * sin + in->axis[Y] * cos;
	out->axis[Z] = in->axis[Z];
}
