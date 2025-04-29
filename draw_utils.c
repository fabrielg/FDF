/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfrancoi <gfrancoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:21:49 by gfrancoi          #+#    #+#             */
/*   Updated: 2025/04/29 19:34:13 by gfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./libft/libft.h"

void	generate_background(t_fdf *fdf)
{
	ft_super_memset(fdf->img_datas.addr,
		&fdf->map.bg_color,
		WIN_HEIGHT * WIN_WIDTH,
		sizeof(int));
}
