/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:44:23 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/07 16:57:40 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate(t_data *data, double angle)
{
	double x;
	double y;

	x = data->vector_x * cos(angle / (180 / M_PI)) + data->vector_y *
	sin(angle / (180 / M_PI));
	y = -data->vector_x * sin(angle / (180 / M_PI)) + data->vector_y *
	cos(angle / (180 / M_PI));
	data->vector_x_mod = x;
	data->vector_y_mod = y;
}

void	ft_rotate_l(t_data *data)
{
	ft_rotate(data, -3);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
}

void	ft_rotate_r(t_data *data)
{
	ft_rotate(data, 3);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
}
