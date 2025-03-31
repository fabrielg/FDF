/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 15:02:45 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "matrix.h"

# define X 0
# define Y 1
# define Z 2

typedef struct s_point3
{
	t_vector3	v;
	int			color;
}	t_point3;

typedef struct s_point2
{
	t_vector2	v;
	int			color;
}	t_point2;

typedef struct s_fdf
{
	t_point3	**origin_map;
	t_point2	**projected_map;
	int			nb_rows;
	int			nb_cols;
}	t_fdf;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

int		parse(t_point3 ***map, int fd, int *nb_rows, int *nb_columns);
int		free_map(t_point3 **map);
void	put_pixel(t_data *data, int x, int y, int color);
void	draw_line(t_vector2 point0, t_vector2 point1, t_data *img, int color);

#endif