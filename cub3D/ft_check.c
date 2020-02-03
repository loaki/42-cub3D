/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 12:25:25 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/03 15:22:57 by jfeuilla         ###   ########.fr       */
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

}
