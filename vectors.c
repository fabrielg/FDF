/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:35:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 19:37:35 by gfrancoi         ###   ########.fr       */
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
