/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/06 17:46:45 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

# define X 0
# define Y 1
# define Z 2

typedef struct s_vector3
{
	int	axis[3];
}	t_vector3;

typedef struct s_vector2
{
	int	axis[2];
}	t_vector2;

typedef struct s_vector3f
{
	float	axis[3];
}	t_vector3f;

typedef struct s_vector2f
{
	float	axis[2];
}	t_vector2f;

t_vector3	vector3f_to_vector3(t_vector3f v3f);
t_vector3f	vector3_to_vector3f(t_vector3 v3);

#endif