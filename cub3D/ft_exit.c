/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:44:49 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/03 20:04:47 by jfeuilla         ###   ########.fr       */
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
	free(data);
	return (EXIT_FAILURE);
}

int		ft_clearimg(t_data *data, int s)
{
	int i;

	i = 0;
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (s > 5)
	{
		mlx_destroy_image(data->mlx_ptr, data->minimap->img_ptr);
		free(data->minimap);
	}
	if (s > 4)
	{
		while (i < NB_TEXTURES)
		{
			if (data->t_path[i])
			{
				mlx_destroy_image(data->mlx_ptr, data->tex[i]->img_ptr);
				free(data->tex[i]);
			}
			i++;
		}
	}
	if (s > 3)
	{
		mlx_destroy_image(data->mlx_ptr, data->health[0]->img_ptr);
		mlx_destroy_image(data->mlx_ptr, data->health[1]->img_ptr);
		free(data->health[0]);
		free(data->health[1]);
	}
	if (s > 2)
	{
		mlx_destroy_image(data->mlx_ptr, data->gameover->img_ptr);
		free(data->gameover);
	}
	if (s > 1)
	{
		i = 0;
		while (i < 4)
		{
			mlx_destroy_image(data->mlx_ptr, data->gun[i]->img_ptr);
			free(data->gun[i]);
			i++;
		}
	}
	if (s > 0)
	{
		mlx_destroy_image(data->mlx_ptr, data->view->img_ptr);
		free(data->view);
	}
	free(data->mlx_ptr);
	return (ft_clearmap(data));
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
	system("leaks a.out");
	exit(0);
	return (0);
}

int		ft_success(t_data *data)
{
	ft_clear_lst(data);
	ft_clearimg(data, 6);
	system("leaks a.out");
	exit(0);
	return (0);
}
