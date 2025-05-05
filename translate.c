/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 22:25:41 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 22:31:52 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	translate_x(t_map *map, int offset)
{
	map->offsets.axis[X] += offset;
}

void	translate_y(t_map *map, int offset)
{
	map->offsets.axis[Y] += offset;
}
