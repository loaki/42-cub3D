/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:25:25 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/07 16:38:09 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (EXIT_FAILURE);
		i++;
	}
	if (str1[i] != str2[i])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_mapname(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	if (i - 1 < 0 || str[i - 1] != 'b')
		return (EXIT_FAILURE);
	if (i - 2 < 0 || str[i - 2] != 'u')
		return (EXIT_FAILURE);
	if (i - 3 < 0 || str[i - 3] != 'c')
		return (EXIT_FAILURE);
	if (i - 4 < 0 || str[i - 4] != '.')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_checkmap(t_data *data)
{
	int x;
	int y;

	y = -1;
	if (data->pos_x == 0 || data->pos_y == 0)
		return (ft_clearmap(data));
	while (data->map[++y])
	{
		x = -1;
		if (data->map[y][0] != '1')
			return (ft_clearmap(data));
		while (data->map[y][++x])
			if (y == 0 && data->map[y][x] != '1')
				return (ft_clearmap(data));
		if (data->map[y][x - 1] != '1' || x != data->width)
			return (ft_clearmap(data));
	}
	x = -1;
	while (data->map[y - 1][++x])
		if (data->map[y - 1][x] != '1')
			return (ft_clearmap(data));
	if (y != data->height)
		return (ft_clearmap(data));
	return (EXIT_SUCCESS);
}

int		ft_checkpath(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < NB_TEXTURES)
	{
		j = 0;
		while (j < i)
		{
			if (data->t_path[j] != 0 &&
				data->t_path[i] != 0 &&
				!ft_strcmp(data->t_path[i], data->t_path[j]))
				return (ft_clearmap(data));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
