/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:57:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/10 17:15:06 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

static t_height_color	parse_data(char *data)
{
	t_height_color	res;
	char			**values;

	res.height = 0;
	res.color = 0x00FFFFFF;
	values = ft_split(data, ',');
	if (!values)
		return (res);
	res.height = ft_atoi(values[0]);
	if (values[1] && !ft_strncmp(values[1], "0x", 2))
		res.color = ft_atoi_base(values[1] + 2, "0123456789ABCDEF");
	free_split(values);
	return (res);
}

static size_t	nb_cols(char **datas)
{
	size_t	count;

	count = 0;
	while (datas && datas[count])
		count++;
	return (count);
}

static int	init_lines(t_height_color ***map, t_list **lines, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(lines, ft_lstnew(line));
		line = get_next_line(fd);
	}
	(*map) = ft_calloc(ft_lstsize(*lines) + 1, sizeof(t_height_color *));
	return (!!(*map));
}

static int	fill_datas(t_height_color ***map, t_list *lines)
{
	char	**line_datas;
	size_t	i;
	size_t	j;

	i = 0;
	while (lines)
	{
		line_datas = ft_split(lines->content, ' ');
		(*map)[i] = ft_calloc(nb_cols(line_datas) + 1, sizeof(t_height_color));
		if (!(*map)[i])
		{
			free_split(line_datas);
			return (!free_map(*map));
		}
		j = 0;
		while (line_datas && line_datas[j])
		{
			(*map)[i][j] = parse_data(line_datas[j]);
			j++;
		}
		free_split(line_datas);
		i++;
		lines = lines->next;
	}
	return (1);
}

t_height_color	**parse(int fd)
{
	t_height_color	**map;
	t_list			*lines;

	if (fd < 0)
		return (NULL);
	lines = NULL;
	if (!init_lines(&map, &lines, fd))
	{
		ft_lstclear(&lines, free);
		return (NULL);
	}
	if (!fill_datas(&map, lines))
	{
		ft_lstclear(&lines, free);
		return (NULL);
	}
	ft_lstclear(&lines, free);
	return (map);
}
