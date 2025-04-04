/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:57:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/31 20:02:58 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

static t_point3	parse_data(char *data, int x, int y)
{
	t_point3	res;
	char		**values;

	res.v.axis[0] = x;
	res.v.axis[1] = y;
	res.v.axis[2] = 0;
	res.color = 0x00FFFFFF;
	values = ft_split(data, ',');
	if (!values)
		return (res);
	res.v.axis[2] = ft_atoi(values[0]);
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
		if (!(*map)[i])
		{
			free_split(line_datas);
			return (!free_map((void **)(*map)));
		}
		j = -1;
		while (line_datas && line_datas[++j])
			(*map)[i][j] = parse_data(line_datas[j], i, j);
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
}
