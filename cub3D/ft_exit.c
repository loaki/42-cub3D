/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:44:49 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/31 13:42:16 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_clearmap(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	i = 0;
	while (i < NB_TEXTURES)
	{
		if (data->t_path[i])
			free(data->t_path[i]);
		i++;
	}
	return (EXIT_FAILURE);
}

int		ft_error(char *str)
{
	int i;

	i = 0;
	write(1, "Error\n", 6);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(0);
	return (0);
}

int		ft_success(t_data *data)
{
	free(data);
	exit(0);
	return (0);
}
