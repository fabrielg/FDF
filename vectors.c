/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:35:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/07 11:46:52 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vector3	vector3f_to_vector3(t_vector3f v3f)
{
	t_vector3	v3;

	v3.axis[X] = v3f.axis[X];
	v3.axis[Y] = v3f.axis[Y];
	v3.axis[Z] = v3f.axis[Z];
	return (v3);
}

t_vector3f	vector3_to_vector3f(t_vector3 v3)
{
	t_vector3f	v3f;

	v3f.axis[X] = v3.axis[X];
	v3f.axis[Y] = v3.axis[Y];
	v3f.axis[Z] = v3.axis[Z];
	return (v3f);
}

t_vector2	vector2f_to_vector2(t_vector3f v2f)
{
	t_vector2	v2;

	v2.axis[X] = v2f.axis[X];
	v2.axis[Y] = v2f.axis[Y];
	return (v2);
}

t_vector2f	vector2_to_vector2f(t_vector2 v2)
{
	t_vector2f	v2f;

	v2f.axis[X] = v2.axis[X];
	v2f.axis[Y] = v2.axis[Y];
	return (v2f);
}
