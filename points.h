/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:41:51 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 17:47:43 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINTS_H
# define POINTS_H

# include "vectors.h"

typedef struct s_point3
{
	t_vector3	v;
	int			color;
	int			default_color;
}	t_point3;

typedef struct s_point2
{
	t_vector2	v;
	int			color;
	int			default_color;
}	t_point2;

#endif
