/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:13:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/16 17:11:13 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"
#include <math.h>

static void	init_vars(t_fdf *fdf)
{
	fdf->origin_map = NULL;
	fdf->projected_map = NULL;
	fdf->nb_rows = 0;
	fdf->nb_cols = 0;
	fdf->mlx = NULL;
	fdf->window = NULL;
	fdf->img.addr = NULL;
	fdf->img.bg_color = 0;
	fdf->img.bits_per_pixel = 8;
	fdf->img.default_scale = 1;
	fdf->img.endian = 0;
	fdf->img.height = 0;
	fdf->img.width = 0;
	fdf->img.line_length = 0;
	fdf->img.offsets[X] = 0;
	fdf->img.offsets[Y] = 0;
	fdf->img.img = NULL;
	fdf->window_width = 0;
	fdf->window_height = 0;
	ft_memset(fdf->min_points, 0, sizeof(t_point2) * 2);
	ft_memset(fdf->max_points, 0, sizeof(t_point2) * 2);
}

int	init_fdf(t_fdf *fdf, int fd)
{
	init_vars(fdf);
	if (!parse(&(fdf->origin_map), fd, &(fdf->nb_rows), &(fdf->nb_cols)))
		return (0);
	if (!init_projected_map(&fdf->projected_map, fdf->nb_rows, fdf->nb_cols))
		return (0);
	if (!init_window(fdf))
		return (0);
	projection_iso(fdf);
	init_min_max_points(fdf);
	if (!init_scale_and_offsets(fdf))
		return (0);
	projection_iso(fdf);
	if (!fdf->projected_map)
		return (0);
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

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	free_map((void **)fdf->origin_map);
	free_map((void **)fdf->projected_map);
}
