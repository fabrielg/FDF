/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:57:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/06 17:51:58 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

static int	free_2d_array(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (1);
}

static int	init_map(t_height_color	**map)
{
	int	nb_lines;
	int	nb_columns;
	int	i;

	map = ft_calloc(nb_lines + 1, sizeof(*map));
	if (!map)
		return (0);
	i = 0;
	while (i < nb_lines)
	{
		map[i] = ft_calloc(nb_columns + 1, sizeof((*map)[i]));
		if (!map[i])
			return (!free_2d_array(map));
		i++;
	}
	return (1);
}

t_height_color	**parse(int fd)
{
	t_height_color	**map;
	char			*line;
	char			**datas;
	int				i;
	int				j;

	if (fd < 0)
		return (NULL);
	line = NULL;
	line = get_next_line(fd);
	j = 0;
	while (line)
	{
		datas = ft_split(line, ' ');
		if (datas)
		{
			i = 0;
			while (datas[i])
			{
				ft_printf("Point 3D: x:%d y:%d z:%s\n", i, j, datas[i]);
				i++;
			}
			j++;
			free_2d_array(datas);
		}
		free(line);
		line = get_next_line(fd);
	}
	get_next_line(-42);
	return (map);
}
