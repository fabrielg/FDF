/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/28 15:53:33 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include "./mlx/mlx.h"
#include "./mlx/mlx_int.h"
#include "matrix.h"
#include <fcntl.h>
#include <math.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || WINDOW_WIDTH < x || y < 0 || WINDOW_HEIGHT < y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	free_map(t_point3 **map)
{
	size_t	i;

	if (!map)
		return (0);
	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
	return (1);
}

int	projection_iso(t_point3 **src, t_point2 **dst, int nb_rows, int nb_cols)
{
	static float	angle = M_PI / 4;
	float			cos_a;
	float			sin_a;
	int				i;
	int				j;

	cos_a = cos(angle);
	sin_a = sin(angle);
	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (j < nb_cols)
		{
			dst[i][j].v.axis[0] = (cos_a * src[i][j].v.axis[0] - cos_a * src[i][j].v.axis[1]) * 20;
			dst[i][j].v.axis[1] = (sin_a * src[i][j].v.axis[0] + sin_a * src[i][j].v.axis[1] - src[i][j].v.axis[2]) * 20;
			dst[i][j].v.axis[0] += 500;
			dst[i][j].v.axis[1] += 500;
			dst[i][j].color = src[i][j].color;
			j++;
		}
		i++;
	}
	return (1);
}

int	init_projected_map(t_point2 ***pm, int nb_rows, int nb_cols)
{
	int	i;

	*pm = ft_calloc(nb_rows + 1, sizeof(t_point2 *));
	if (!(*pm))
		return (0);
	i = 0;
	while (i < nb_rows)
	{
		(*pm)[i] = ft_calloc(nb_cols + 1, sizeof(t_point2));
		if (!(*pm)[i])
			return (0);
		i++;
	}
	return (1);
}

int	init_fdf(t_fdf *fdf, int fd)
{
	fdf->origin_map = NULL;
	fdf->projected_map = NULL;
	fdf->nb_rows = 0;
	fdf->nb_cols = 0;
	if (!parse(&(fdf->origin_map), fd, &(fdf->nb_rows), &(fdf->nb_cols)))
		return (0);
	if (!init_projected_map(&fdf->projected_map, fdf->nb_rows, fdf->nb_cols))
		return (0);
	projection_iso(fdf->origin_map, fdf->projected_map, fdf->nb_rows, fdf->nb_cols);
	if (!fdf->projected_map)
		return (0);
	return (1);
}

void	draw_map(t_point2 **map, int nb_rows, int nb_cols, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (j < nb_cols)
		{
			if (j + 1 < nb_cols)
				draw_line(map[i][j].v, map[i][j + 1].v, img, map[i][j].color);
			if (i + 1 < nb_rows)
				draw_line(map[i][j].v, map[i + 1][j].v, img, map[i][j].color);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	int		fd;
	void	*mlx;
	void	*window;
	t_data	img;

	if (ac != 2)
		return (ft_putendl_fd("Usage: ./fdf <filename>", 1), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error: invalid fd", 1), 0);
	if (!init_fdf(&fdf, fd) || !fdf.origin_map || !fdf.projected_map)
	{
		ft_putendl_fd("INIT FDF ERROR", 1);
		return (0);
	}
	close(fd);
	mlx = mlx_init();
	window = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	draw_map(fdf.projected_map, fdf.nb_rows, fdf.nb_cols, &img);
	free_map(fdf.origin_map);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
