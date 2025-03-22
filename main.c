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
#include <fcntl.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

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

void	draw_grid(t_point **map, size_t nb_rows, size_t nb_cols, t_data *img)
{
	t_point p_origin;
	t_point p_right;
	t_point p_down;
	size_t	i;
	size_t	j;
	size_t	length;

	i = 0;
	length = 50;
	while (i < nb_cols)
	{
		j = 0;
		while (j < nb_rows)
		{
			p_origin = map[i][j];
			p_origin.axis[0] *= length;
			p_origin.axis[1] *= length;
			if (i + 1 < nb_cols)
			{
				p_right = map[i + 1][j];
				p_right.axis[0] *= length;
				p_right.axis[1] *= length;
				draw_line(p_origin, p_right, img, p_origin.color);
			}
			if (j + 1 < nb_rows)
			{
				p_down = map[i][j + 1];
				p_down.axis[0] *= length;
				p_down.axis[1] *= length;
				draw_line(p_origin, p_down, img, p_origin.color);
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_point	**map;
	int		fd;
	void	*mlx;
	void	*window;
	t_data	img;

	if (ac != 2)
		return (ft_putendl_fd("Usage: ./fdf <filename>", 1), 0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Error: invalid fd", 1), 0);
	map = parse(fd);
	if (!map)
	{
		ft_putendl_fd("MAP IS NULL", 1);
		return (0);
	}
	ft_printf("TEST: x:%d y:%d z:%d color:%x\n", map[2][2].axis[0], map[2][2].axis[1], map[2][2].axis[2], map[2][2].color);
	close(fd);
	mlx = mlx_init();
	window = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	draw_grid(map, 6, 10, &img);
	free_map(map);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
