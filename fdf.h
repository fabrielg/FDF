/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/07 16:27:27 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "matrix.h"

# define X 0
# define Y 1
# define Z 2

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900

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

typedef struct s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	float	default_scale;
	int		offsets[2];
	int		bg_color;
}	t_img_data;

typedef struct s_fdf
{
	t_point3	**origin_map;
	t_point2	**projected_map;
	int			nb_rows;
	int			nb_cols;
	void		*mlx;
	void		*window;
	t_img_data	img;
	int			window_width;
	int			window_height;
	t_point2	*min_points[2];
	t_point2	*max_points[2];
}	t_fdf;

int		parse(t_point3 ***map, int fd, int *nb_rows, int *nb_columns);
int		init_fdf(t_fdf *fdf, int fd);
int		init_projected_map(t_point2 ***pm, int nb_rows, int nb_cols);
int		free_map(void **map);
void	put_pixel(t_img_data *data, int x, int y, int color);
void	draw_line(t_vector2 point0, t_vector2 point1, t_img_data *img, int color);
void	init_min_max_points(t_fdf *fdf);
void	init_scale_and_offsets(t_fdf *fdf);
void	projection_iso(t_fdf *fdf);
void	draw_map(t_point2 **map, int nb_rows, int nb_cols, t_img_data *img);
int		init_window(t_fdf *fdf);
int		close_window(t_fdf *fdf);

#endif