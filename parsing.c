/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:57:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/16 21:32:17 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

static t_list	*get_lines_from_file(int fd)
{
	t_list	*lines;
	char	*temp_line;

	lines = NULL;
	temp_line = get_next_line(fd);
	while (temp_line)
	{
		ft_lstadd_back(&lines, ft_lstnew(temp_line));
		temp_line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

static int	parse_line(const char *line, t_point3 **p, int y, int *cols)
{
	char	**split;
	char	*end;
	int		x;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	*cols = ft_min(*cols, ft_strarrlen(split));
	*p = malloc(*cols * sizeof(t_point3));
	if (!*p)
		return (free_split(split), 0);
	x = 0;
	while (x < *cols)
	{
		(*p + x)->color = 0xFFFFFF;
		(*p + x)->v.axis[X] = x;
		(*p + x)->v.axis[Y] = y;
		(*p + x)->v.axis[Z] = ft_atoi(split[x]);
		end = ft_strchr(split[x], ',');
		if (end && !ft_strncmp(end, ",0x", 3))
			(*p + x)->color = ft_atoi_base(end + 3, "0123456789ABCDEF");
		x++;
	}
	free_split(split);
	return (1);
}

static t_point3	**get_map_from_lines(t_list *lines, int nb_rows, int *nb_cols)
{
	t_point3	**map;
	int			i;

	map = malloc(nb_rows * sizeof(t_point3 *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < nb_rows)
	{
		if (!parse_line(lines->content, map + i, i, nb_cols))
		{
			ft_free_map((void **)map, i);
			return (NULL);
		}
		lines = lines->next;
		i++;
	}
	return (map);
}

int	parse(t_point3 ***map, int fd, int *nb_rows, int *nb_columns)
{
	t_list	*lines;

	if (fd < 0)
		return (0);
	lines = get_lines_from_file(fd);
	if (!lines)
		return (0);
	*nb_rows = ft_lstsize(lines);
	*nb_columns = 2147483647;
	(*map) = get_map_from_lines(lines, *nb_rows, nb_columns);
	if (!*map)
	{
		ft_lstclear(&lines, free);
		return (0);
	}
	ft_lstclear(&lines, free);
	return (1);
}
