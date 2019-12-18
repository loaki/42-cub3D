/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:06:41 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/18 16:39:20 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_size_wall_xp(t_data *data, t_pos *pos, double x, double y)
{
	double i;

	i = 0;
	while (x < data->width && y < data->height && x != 0)
	{
		if ((int)(pos->x + 1) == (int)(pos->x + 0.5))
		{
			x = (int)(pos->x + 1) + i;
			y = pos->y + fabs(x - pos->x) / pos->vector_x_mod * pos->vector_y_mod;
		}
		else
		{
			x = (int)(pos->x) + i;
			y = pos->y + fabs(x - pos->x) / pos->vector_x_mod * pos->vector_y_mod;
		}
		if ((int)y <= data->height && data->map[(int)x][(int)y] != '0')
		{
			return (data->height / (sqrt((pos->x - x) * (pos->x - x) +
			(pos->y - y) * (pos->y - y))));
		}
		i++;
	}
	return (0);
}

double	ft_size_wall_xn(t_data *data, t_pos *pos, double x, double y)
{
	double i;

	i = 0;
	while (x < data->width && y < data->height && x != 0)
	{
		if ((int)(pos->x - 1) == (int)(pos->x - 0.5))
		{
			x = (int)(pos->x - 1) - i;
			y = pos->y + fabs(x - pos->x) / pos->vector_x_mod * pos->vector_y_mod;
		}
		else
		{
			x = (int)(pos->x) - i;
			y = pos->y + fabs(x - pos->x) / pos->vector_x_mod * pos->vector_y_mod;
		}
		if ((int)y <= data->height && data->map[(int)x][(int)y] != '0')
		{
			return (data->height / (sqrt((pos->x - x) * (pos->x - x) +
			(pos->y - y) * (pos->y - y))));
		}
		i++;
	}
	return (0);
}

double	ft_size_wall_yp(t_data *data, t_pos *pos, double x, double y)
{
	double i;

	i = 0;
	while (x < data->width && y < data->height && y != 0)
	{
		if ((int)(pos->y + 1) == (int)(pos->y + 0.5))
		{
			y = (int)(pos->y + 1) + i;
			x = pos->x + fabs(y - pos->y) / pos->vector_y_mod * pos->vector_x_mod;
		}
		else
		{
			y = (int)(pos->y) + i;
			x = pos->x + fabs(y - pos->y) / pos->vector_y_mod * pos->vector_x_mod;
		}
		if ((int)x <= data->width && data->map[(int)x][(int)y] != '0')
		{
			return (data->height / (sqrt((pos->x - x) * (pos->x - x) +
			(pos->y - y) * (pos->y - y))));
		}
		i++;
	}
	return (0);
}

double	ft_size_wall_yn(t_data *data, t_pos *pos, double x, double y)
{
	double i;

	i = 0;
	while (x < data->width && y < data->height && y != 0)
	{
		if ((int)(pos->y - 1) == (int)(pos->y - 0.5))
		{
			y = (int)(pos->y - 1) - i;
			x = pos->x + fabs(y - pos->y) / pos->vector_y_mod * pos->vector_x_mod;
		}
		else
		{
			y = (int)(pos->y) - i;
			x = pos->x + fabs(y - pos->y) / pos->vector_y_mod * pos->vector_x_mod;
		}
		if ((int)x <= data->width && data->map[(int)x][(int)y] != '0')
		{
			return (data->height / (sqrt((pos->x - x) * (pos->x - x) +
			(pos->y - y) * (pos->y - y))));
		}
		i++;
	}
	return (0);
}
