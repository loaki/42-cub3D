/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:06:41 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 14:09:51 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_size_wall_xp(t_data *data, double x, double y)
{
	double i;

	i = 0;
	while (x < data->height && y < data->width && x != 0)
	{
		if ((int)(data->pos_x + 1) == (int)(data->pos_x + 0.5))
		{
			x = (int)(data->pos_x + 1) + i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		else
		{
			x = (int)(data->pos_x) + i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		if ((int)y <= data->width && data->map[(int)y][(int)x] != '0')
		{
			return (data->height / (sqrt((data->pos_x - x) * (data->pos_x - x) +
			(data->pos_y - y) * (data->pos_y - y))));
		}
		i++;
	}
	return (0);
}

double	ft_size_wall_xn(t_data *data, double x, double y)
{
	double i;

	i = 0;
	while (x < data->height && y < data->width && x != 0)
	{
		if ((int)(data->pos_x - 1) == (int)(data->pos_x - 0.5))
		{
			x = (int)(data->pos_x - 1) - i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		else
		{
			x = (int)(data->pos_x) - i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		if ((int)y <= data->width && data->map[(int)y][(int)x] != '0')
		{
			return (data->height / (sqrt((data->pos_x - x) * (data->pos_x - x) +
			(data->pos_y - y) * (data->pos_y - y))));
		}
		i++;
	}
	return (0);
}

double	ft_size_wall_yp(t_data *data, double x, double y)
{
	double i;

	i = 0;
	while (x < data->height && y < data->width && y != 0)
	{
		if ((int)(data->pos_y + 1) == (int)(data->pos_y + 0.5))
		{
			y = (int)(data->pos_y + 1) + i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		else
		{
			y = (int)(data->pos_y) + i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		if ((int)x <= data->height && data->map[(int)y][(int)x] != '0')
		{
			return (data->height / (sqrt((data->pos_x - x) * (data->pos_x - x) +
			(data->pos_y - y) * (data->pos_y - y))));
		}
		i++;
	}
	return (0);
}

double	ft_size_wall_yn(t_data *data, double x, double y)
{
	double i;

	i = 0;
	while (x < data->height && y < data->width && y != 0)
	{
		if ((int)(data->pos_y - 1) == (int)(data->pos_y - 0.5))
		{
			y = (int)(data->pos_y - 1) - i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		else
		{
			y = (int)(data->pos_y) - i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		if ((int)x <= data->height && data->map[(int)y][(int)x] != '0')
		{
			return (data->height / (sqrt((data->pos_x - x) * (data->pos_x - x) +
			(data->pos_y - y) * (data->pos_y - y))));
		}
		i++;
	}
	return (0);
}
