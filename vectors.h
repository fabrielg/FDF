/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/02 15:56:16 by gfrancoi         ###   ########.fr       */
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

#endif