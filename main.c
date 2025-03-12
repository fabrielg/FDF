/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:20:02 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/12 16:58:24 by gfrancoi         ###   ########.fr       */
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

void	draw_grid(t_height_color **map)
{
	t_point p1;
	t_point p2;
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
	if (map)
		ft_printf("TEST: %d %x\n", map[2][2].height, map[2][2].color);
	else
		ft_putendl_fd("MAP IS NULL", 1);
	close(fd);
	free_map(map);
	mlx = mlx_init();
	window = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	img.img = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, \
		&img.line_length, &img.endian);
	t_point p1;
	t_point p2;

	p1.x = 0;
	p1.y = 0;
	p2.x = WINDOW_WIDTH;
	p2.y = WINDOW_HEIGHT;
	draw_line(p1, p2, &img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
