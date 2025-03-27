/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 17:24:55 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_vector3 m_multiply3(float matrix[3][3], t_vector3 point)
{
    t_vector3 result;
    int     i;
    int     j;

    result = point;
    i = 0;
    while (i < 3)
    {
        result.axis[i] = 0;
        j = 0;
       while (j < 3)
        {
            result.axis[i] += matrix[i][j] * point.axis[j];
            j++;
        }
        i++;
    }
    return (result);
}

void    rotate_x(t_vector3 *point, t_vector3 *projection, float angle, int len)
{
    float   matrix_x_rotation[3][3];
    float   rad;
    int     i;

    if (!point || !projection)
        return ;
    rad = angle * M_PI / 180;
    matrix_x_rotation[0][0] = 1;
    matrix_x_rotation[0][1] = 0;
    matrix_x_rotation[0][2] = 0;
    matrix_x_rotation[1][0] = 0;
    matrix_x_rotation[1][1] = cos(rad);
    matrix_x_rotation[1][2] = -sin(rad);
    matrix_x_rotation[2][0] = 0;
    matrix_x_rotation[2][1] = sin(rad);
    matrix_x_rotation[2][2] = cos(rad);
    i = -1;
    while (++i < len)
        projection[i] = m_multiply3(matrix_x_rotation, point[i]);
}

void    rotate_y(t_vector3 *point, t_vector3 *projection, float angle, int len)
{
    float   matrix_y_rotation[3][3];
    float   rad;
    int     i;

    if (!point || !projection)
        return ;
    rad = angle * M_PI / 180;
    matrix_y_rotation[0][0] = cos(rad);
    matrix_y_rotation[0][1] = 0;
    matrix_y_rotation[0][2] = sin(rad);
    matrix_y_rotation[1][0] = 0;
    matrix_y_rotation[1][1] = 1;
    matrix_y_rotation[1][2] = 0;
    matrix_y_rotation[2][0] = -sin(rad);
    matrix_y_rotation[2][1] = 0;
    matrix_y_rotation[2][2] = cos(rad);
    i = -1;
    while (++i < len)
        projection[i] = m_multiply3(matrix_y_rotation, point[i]);
}
