/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:55:27 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/05/06 21:23:23 by gfrancoi         ###   ########.fr       */
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

typedef struct s_map_color
{
	unsigned int	bottom;
	unsigned int	ground;
	unsigned int	top;
}	t_map_color;

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_map	t_map;
typedef t_vector2		(*t_proj_func)(t_map*, t_vector3f);
struct s_map
{
	t_point3	**points;
	t_point2	**proj;
	t_vector2	limits[2];
	t_vector2	offsets;
	t_proj_func	proj_function;
	t_map_color	colors;
	int			size;
	int			cols;
	int			rows;
	float		camera[3];
	float		scale;
	float		scale_min;
	float		scale_max;
	float		z_coeff;
	float		radius;
	int			menu_width;
	int			bg_color;
	int			globe;
};

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
void		change_proj_function(t_fdf *fdf, char proj);
t_vector2	projection_iso(t_map *map, t_vector3f v3f);
t_vector2	projection_ortho(t_map *map, t_vector3f v3f);
void		apply_projection(t_map *map);
void		generate_projection(t_map *map, int fit);
void		generate_background(t_fdf *fdf);
void		set_limits(t_map *map);
void		set_scale(t_map *map);
void		set_offsets(t_map *map);
void		set_polar_points(t_map *map);
void		spherize(t_map *map, t_vector3f *v3f, t_vector2f polar);
void		rotate_x(t_vector3f *in, t_vector3f *out, float angle);
void		rotate_y(t_vector3f *in, t_vector3f *out, float angle);
void		rotate_z(t_vector3f *in, t_vector3f *out, float angle);
void		translate_x(t_map *map, int offset);
void		translate_y(t_map *map, int offset);
void		next_color(t_map *map, int step);
void		color_map(t_map *map);
int			lerp_rgb(int c1, int c2, float t);
int			key_press(int keycode, t_fdf *fdf);
int			mouse_action(int button, int x, int y, void *param);
void		draw_map(t_fdf *fdf, int fit);

#endif