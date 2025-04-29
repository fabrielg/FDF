/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:13:36 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 14:14:38 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "keycodes.h"
#include "./libft/libft.h"
#include <math.h>

static void	init_img(t_img_data *image)
{
	image->addr = NULL;
	image->bg_color = 0;
	image->bits_per_pixel = 8;
	image->default_scale = 1;
	image->scale = image->default_scale;
	image->endian = 0;
	image->height = 0;
	image->width = 0;
	image->line_length = 0;
	image->proj = KEY_I;
	image->offsets[X] = 0;
	image->offsets[Y] = 0;
	image->z_divisor = 0.1f;
	image->img = NULL;
}

static int	init_copy_map(t_fdf *fdf)
{
	int	y;
	int	size;

	size = fdf->nb_cols * sizeof(t_point3);
	fdf->copy = malloc(size);
	if (!fdf->copy)
		return (0);
	y = 0;
	while (y < fdf->nb_rows)
	{
		fdf->copy[y] = malloc(fdf->nb_cols * sizeof(t_point3));
		if (!fdf->copy[y])
		{
			ft_free_map((void **)fdf->copy, y);
			return (0);
		}
		ft_memcpy(fdf->copy[y], fdf->origin_map[y], size);
		y++;
	}
	return (1);
}

int	init_fdf(t_fdf *fdf, int fd)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	init_img(&fdf->projection);
	init_img(&fdf->menu);
	if (!parse(&(fdf->origin_map), fd, &(fdf->nb_rows), &(fdf->nb_cols)))
		return (0);
	if (!init_copy_map(fdf))
		return (0);
	if (!init_projected_map(&fdf->projected_map, fdf->nb_rows, fdf->nb_cols))
		return (0);
	if (!init_window(fdf))
		return (0);
	project(fdf);
	init_min_max_points(fdf);
	if (!init_scale_and_offsets(fdf))
		return (0);
	project(fdf);
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

void	free_fdf(t_fdf *fdf)
{
	if (!fdf)
		return ;
	ft_free_map((void **)fdf->origin_map, fdf->nb_rows);
	ft_free_map((void **)fdf->copy, fdf->nb_rows);
	ft_free_map((void **)fdf->projected_map, fdf->nb_rows);
}
