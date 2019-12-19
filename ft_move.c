/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:20:47 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 16:32:32 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_collision(t_data *data)
{
	if (data->map[(int)data->pos_x][(int)data->pos_y] != '0')
		return (1);
	return (0);
}
void	ft_move_f(t_data *data)
{
	data->pos_x += data->vector_x;
	data->pos_y -= data->vector_y;
	if (ft_collision(data) == 1)
	{
		data->pos_x -= data->vector_x;
		data->pos_y += data->vector_y;
	}
	ft_info(data);
	ft_view(data);
}
void	ft_move_b(t_data *data)
{
	data->pos_x -= data->vector_x;
	data->pos_y += data->vector_y;
	if (ft_collision(data) == 1)
	{
		data->pos_x += data->vector_x;
		data->pos_y -= data->vector_y;
	}
	ft_info(data);
	ft_view(data);
}
void	ft_move_l(t_data *data)
{
	ft_rotate(data, -10);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
	ft_info(data);
	ft_view(data);
	
}
void	ft_move_r(t_data *data)
{
	ft_rotate(data, 10);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
	ft_info(data);
	ft_view(data);
}

void ft_info(t_data *data)
{
	printf("\n----------\nx = |%f| y = |%f|\n", data->pos_x, data->pos_y);
	printf("vect x = |%f| vect y = |%f|\n", data->vector_x, data->vector_y);
}
