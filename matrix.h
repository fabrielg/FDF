/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 17:07:11 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "fdf.h"

typedef struct s_vector3
{
	int	axis[3];
}	t_vector3;

typedef struct s_vector2
{
	int	axis[2];
}	t_vector2;

t_vector3	m_multiply3(float matrix[3][3], t_vector3 point);
void		rotate_x(t_vector3 *p, t_vector3 *projection, float angle, int len);
void		rotate_y(t_vector3 *p, t_vector3 *projection, float angle, int len);

#endif