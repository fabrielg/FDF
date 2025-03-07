/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:57:08 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/03/07 19:14:04 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

static int	free_map(t_height_color	**map)
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
	return (res);
}

static t_height_color	**split_datas(char *datas)
{
	t_height_color	**map;
	char			**lines;
	char			**line_datas;
	int				i;
	int				j;

	map = NULL;
	lines = ft_split(datas, '\n');
	i = 0;
	line_datas = NULL;
	while (lines[i])
	{
		line_datas = ft_split(lines[i], ' ');
		j = 0;
		while (line_datas[j])
		{
			ft_printf("Height: %d	Color: %x\n", parse_data(line_datas[j]).height, parse_data(line_datas[j]).color);
			j++;
		}
		if (line_datas)
			free_split(line_datas);
		i++;
	}
	return (map);
}

t_height_color	**parse(int fd)
{
	t_height_color	**map;
	char			*map_content;

	map = NULL;
	free_map(map);
	if (fd < 0)
		return (NULL);
	map_content = get_map_content(fd);
	split_datas(map_content);
	free(map_content);
	return (map);
}
