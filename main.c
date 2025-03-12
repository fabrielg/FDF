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

int	free_map(t_height_color	**map)
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

void	draw_grid(t_height_color **map, size_t nb_rows, size_t nb_cols, t_data *img)
{
	t_point p1;
	t_point p2;
	size_t	i;
	size_t	j;

	i = 0;
	while (i < nb_rows)
	{
		j = 0;
		while (j < nb_cols - 1)
		{
			p1.x = j * 100;
			p1.y = i * 100;
			p2.x = (j + 1) * 100;
			p2.y = i * 100;
			draw_line(p1, p2, img, map[i][j].color);
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_height_color	**map;
	int				fd;
	void			*mlx;
	void			*window;
	t_data			img;

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
	close(fd);
	mlx = mlx_init();
	window = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	draw_grid(map, 10, 10, &img);
	free_map(map);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
