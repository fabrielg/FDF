/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 17:24:55 by gfrancoi         ###   ########.fr       */
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

int	free_map(t_point **map)
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

void	apply_isometric(t_point **src, t_point **dst, int len)
{
	static int	offset = 0;
	int	size = WINDOW_HEIGHT / len;
	int			i;
	int			j;

	i = 0;
	while (dst[i])
	{
		rotate_x(src[i], dst[i], atan(1 / (sqrt(2))) * 180 / M_PI, len);
		rotate_y(src[i], dst[i], 45, len);
		j = 0;
		while (j < len)
		{
			dst[i][j].axis[0] = (size * dst[i][j].axis[0]) + WINDOW_WIDTH / WINDOW_WIDTH;
			dst[i][j].axis[1] = (size * dst[i][j].axis[1]) + WINDOW_HEIGHT / WINDOW_HEIGHT;
			j++;
		}
		i++;
	}
}

void	draw_grid(t_point **map, size_t nb_rows, size_t nb_cols, t_data *img)
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
				draw_line(map[i][j], map[i][j + 1], img, map[i][j].color);
			if (i + 1 < nb_rows)
				draw_line(map[i][j], map[i + 1][j], img, map[i][j].color);
			j++;
		}
		i++;
	}
}

t_point	**map_dup(t_point **src, int nb_rows, int nb_cols)
{
	t_point	**dest;
	int		i;
	int		j;

	dest = ft_calloc(nb_rows + 1, sizeof(t_point *));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < nb_rows)
	{
		dest[i] = ft_calloc(nb_cols + 1, sizeof(t_point));
		if (!dest[i])
			return (NULL);
		j = 0;
		while (j < nb_cols)
		{
			dest[i][j] = src[i][j];
			j++;
		}
		i++;
	}
	return (dest);
}

int	init_fdf(t_fdf *fdf, int fd)
{
	fdf->origin_map = NULL;
	fdf->projected_map = NULL;
	fdf->nb_rows = 0;
	fdf->nb_cols = 0;
	if (!parse(&(fdf->origin_map), fd, &(fdf->nb_rows), &(fdf->nb_cols)))
		return (0);
	fdf->projected_map = map_dup(fdf->origin_map, fdf->nb_rows, fdf->nb_cols);
	if (!fdf->projected_map)
		return (0);
	return (1);
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
	apply_isometric(fdf.origin_map, fdf.projected_map, fdf.nb_cols);
	draw_grid(fdf.projected_map, fdf.nb_rows, fdf.nb_cols, &img);
	free_map(fdf.origin_map);
	free_map(fdf.projected_map);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
