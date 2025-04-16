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

static int	count_columns(const char *line)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*line)
	{
		if (*line != ' ' && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*line == ' ')
			in_word = 0;
		line++;
	}
	return (count);
}

static int	parse_line(t_point3 *row, const char *line, int y)
{
	int		x;
	char	*end;
	char	*data;

	x = 0;
	data = (char *)line;
	while (*data)
	{
		row[x].v.axis[X] = x;
		row[x].v.axis[Y] = y;
		row[x].v.axis[Z] = ft_strtol(data, &end, 10);
		row[x].color = 0xFFFFFF;
		if (*end == ',')
			row[x].color = ft_strtol(end + 1, NULL, 16);
		data = end;
		while (*data == ' ')
			data++;
		x++;
	}
	return (1);
}

static int	fill_datas(t_point3 ***map, t_list *lines, int *nb_columns)
{
	char	**line_datas;
	int		i;
	int		j;

	i = 0;
	while (lines)
	{
		line_datas = ft_split(lines->content, ' ');
		if (!line_datas)
			return (0);
		(*map)[i] = ft_calloc(*nb_columns, sizeof(t_point3));
		if (!(*map)[i])
		{
			free_split(line_datas);
			return (0);
		}
		j = 0;
		while (line_datas[j] && j < *nb_columns)
		{
			(*map)[i][j] = parse_data(line_datas[j], j, i);
			j++;
		}
		free_split(line_datas);
		lines = lines->next;
		i++;
	}
	return (1);
	}

int	parse(t_point3 ***map, int fd, int *nb_rows, int *nb_columns)
{
	t_list	*lines;
	char	*line;

	if (fd < 0)
		return (0);
	lines = NULL;
	*nb_rows = 0;
	while ((line = get_next_line(fd)))
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		(*nb_rows)++;
	}
	if (*nb_rows == 0 || !lines)
		return (0);
	*nb_columns = count_columns(lines->content);
	*map = ft_calloc(*nb_rows, sizeof(t_point3 *));
	if (!(*map) || !fill_datas(map, lines, nb_columns))
	{
		ft_lstclear(&lines, free);
		return (0);
	}
	ft_lstclear(&lines, free);
	return (1);
}
/*
static t_point3	parse_data(char *data, int x, int y)
{
	t_point3	res;
	char		**values;

	res.v.axis[X] = x;
	res.v.axis[Y] = y;
	res.v.axis[Z] = 0;
	res.color = 0x00FFFFFF;
	if (!data)
		return (res);
	values = ft_split(data, ',');
	if (!values)
		return (res);
	res.v.axis[Z] = ft_atoi(values[0]);
	if (values[1] && !ft_strncmp(values[1], "0x", 2))
		res.color = ft_atoi_base(values[1] + 2, "0123456789ABCDEF");
	free_split(values);
	return (res);
}

static int	nb_cols(char **datas)
{
	int	count;

	count = 0;
	while (datas && datas[count])
		count++;
	return (count);
}

static int	init_lines(t_point3 ***map, t_list **lines, int fd, int *nb_lines)
{
	char	*line;

	*nb_lines = 0;
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line)
	{
		ft_lstadd_back(lines, ft_lstnew(line));
		line = get_next_line(fd);
		(*nb_lines)++;
	}
	(*map) = ft_calloc(ft_lstsize(*lines) + 1, sizeof(t_point3 *));
	return (!!(*map));
}

static int	fill_datas(t_point3 ***map, t_list *lines, int *nb_datas)
{
	char	**line_datas;
	int		i;
	int		j;

	i = 0;
	*nb_datas = -1;
	while (lines)
	{
		line_datas = ft_split(lines->content, ' ');
		(*map)[i] = ft_calloc(nb_cols(line_datas) + 1, sizeof(t_point3));
		if (nb_cols(line_datas) < *nb_datas || *nb_datas < 0)
			*nb_datas = nb_cols(line_datas);
		if (!(*map)[i] || !line_datas)
		{
			free_split(line_datas);
			return (0);
		}
		j = -1;
		while (line_datas[++j])
			(*map)[i][j] = parse_data(line_datas[j], j, i);
		free_split(line_datas);
		i++;
		lines = lines->next;
	}
	return (1);
}

int	parse(t_point3 ***map, int fd, int *nb_rows, int *nb_columns)
{
	t_list	*lines;

	if (fd < 0)
		return (0);
	lines = NULL;
	if (!init_lines(map, &lines, fd, nb_rows))
	{
		if (lines)
			ft_lstclear(&lines, free);
		return (0);
	}
	if (!fill_datas(map, lines, nb_columns))
	{
		ft_lstclear(&lines, free);
		return (0);
	}
	ft_lstclear(&lines, free);
	return (1);
}*/
