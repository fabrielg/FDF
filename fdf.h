/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 17:07:11 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>

typedef struct s_point
{
	int	axis[3];
	int	color;
}	t_point;

typedef struct s_fdf
{
	t_point	**origin_map;
	t_point	**projected_map;
	int		nb_rows;
	int		nb_cols;
}	t_fdf;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

int		parse(t_point ***map, int fd, int *nb_rows, int *nb_columns);
int		free_map(t_point **map);
void	put_pixel(t_data *data, int x, int y, int color);
void	draw_line(t_point p0, t_point p1, t_data *img, int color);

#endif