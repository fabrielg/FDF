/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:13:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/07 16:42:34 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include <math.h>

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
	init_window(fdf);
	fdf->img.default_scale = 1;
	fdf->img.offsets[X] = 0;
	fdf->img.offsets[Y] = 0;
	projection_iso(fdf);
	init_min_max_points(fdf);
	init_scale_and_offsets(fdf);
	projection_iso(fdf);
	if (!fdf->projected_map)
		return (0);
	return (1);
}

int	free_map(void **map)
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

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || data->width < x || y < 0 || data->height < y)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_map(t_point2 **map, int nb_rows, int nb_cols, t_img_data *img)
{
	int	i;
	int	j;

	if (!map || !(*map))
		return ;
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
