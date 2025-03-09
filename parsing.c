/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:57:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/08 20:15:40 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

static char	*get_map_content(int fd)
{
	t_strbuilder	*build_content;
	char			*map_content;
	char			c;

	build_content = ft_sb_new();
	while (read(fd, &c, 1))
		ft_sb_add_char(build_content, c);
	map_content = ft_sb_build(build_content);
	ft_sb_clear(&build_content);
	ft_printf("Map :\n%s\n", map_content);
	return (map_content);
}

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

static void	split_datas(char *datas, t_height_color ***map)
{
	size_t	nb_lines;
	size_t	nb_columns;
	char	**lines;
	char	**line_datas;
	int		i;
	int		j;

	lines = ft_split(datas, '\n');
	nb_lines = 0;
	while (lines[nb_lines])
		nb_lines++;
	*map = ft_calloc(nb_lines + 1, sizeof(t_height_color *));
	if (!(*map))
		return ;
	i = 0;
	line_datas = NULL;
	while (lines[i])
	{
		line_datas = ft_split(lines[i], ' ');
		nb_columns = 0;
		while (line_datas && line_datas[nb_columns])
			nb_columns++;
		(*map)[i] = ft_calloc(nb_columns + 1, sizeof(t_height_color));
		if (!(*map)[i])
			return ;
		j = 0;
		while (line_datas && line_datas[j])
		{
			(*map)[i][j] = parse_data(line_datas[j]);
			j++;
		}
		if (line_datas)
			free_split(line_datas);
		i++;
	}
	free_split(lines);
}

t_height_color	**parse(int fd)
{
	t_height_color	**map;
	char			*map_content;

	if (fd < 0)
		return (NULL);
	map = NULL;
	map_content = get_map_content(fd);
	split_datas(map_content, &map);
	free(map_content);
	return (map);
}
