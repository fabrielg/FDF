/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/05 21:08:48 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "points.h"

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900

typedef struct s_rgb
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_rgb;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_map
{
	t_point3	**points;
	t_point2	**proj;
	t_vector2	limits[2];
	t_vector2	offsets;
	int			size;
	int			cols;
	int			rows;
	float		camera[3];
	float		scale;
	float		z_coeff;
	int			menu_width;
	int			bg_color;
}	t_map;

typedef struct s_libx {
	void	*mlx;
	void	*win;
}	t_libx;

typedef struct s_fdf
{
	t_libx		libx;
	t_img_data	img_datas;
	t_map		map;
}	t_fdf;

int			parse_map(t_map *map, int fd);
void		center_map_pivot(t_map *map);
int			init_fdf(t_fdf *fdf, int fd);
void		free_fdf(t_fdf *fdf);
int			close_window(t_fdf *fdf);
void		put_pixel(t_img_data *data, int x, int y, int color);
void		draw_line(t_point2 p0, t_point2 p1, t_img_data *img);
void		apply_projection(t_map *map);
t_vector2	projection_iso(t_map *map, t_vector3f v3f);
void		generate_projection(t_map *map);
void		generate_background(t_fdf *fdf);
void		set_limits(t_map *map);
void		set_scale(t_map *map);
void		set_offsets(t_map *map);
void		rotate_x(t_vector3f *in, t_vector3f *out, float angle);
void		rotate_y(t_vector3f *in, t_vector3f *out, float angle);
void		rotate_z(t_vector3f *in, t_vector3f *out, float angle);
int			lerp_rgb(int c1, int c2, float t);
int			key_press(int keycode, t_fdf *fdf);
void		draw_map(t_fdf *fdf);

#endif