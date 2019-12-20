/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:06:41 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/20 15:26:34 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_size_wall_xp(t_data *data, double x, double y)
{
	double i;

	i = 0;
	while (x < (double)data->width && y < (double)data->height)
	{
		printf("x=%f y=%f\n", x, y);
		if ((int)round((data->pos_x + 1)) == (int)round((data->pos_x + 0.5)))
		{
			x = (int)round((data->pos_x + 1)) + i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		else
		{
			x = (int)round((data->pos_x)) + i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		if ((int)round(y) <= (data->height - 1) && (int)round(x) <= (data->width - 1) && data->map[(int)round(y)][(int)round(x)] != '0')
		{
			return ((double)data->res_y / (sqrtf((data->pos_x - x) * (data->pos_x - x) +
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
	while (x < (double)data->width && y < (double)data->height)
	{
		if ((int)round((data->pos_x - 1)) == (int)round((data->pos_x - 0.5)))
		{
			x = (int)round((data->pos_x - 1)) - i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		else
		{
			x = (int)round((data->pos_x)) - i;
			y = data->pos_y + fabs(x - data->pos_x) / data->vector_x_mod * data->vector_y_mod;
		}
		if ((int)round(x) <= (data->width - 1) && (int)round(y) <= (data->height - 1) && data->map[(int)round(y)][(int)round(x)] != '0')
		{
			return ((double)data->res_y / (sqrtf((data->pos_x - x) * (data->pos_x - x) +
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
	while (x < (double)data->width && y < (double)data->height)
	{
		if ((int)round((data->pos_y + 1)) == (int)round((data->pos_y + 0.5)))
		{
			y = (int)round((data->pos_y + 1)) + i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		else
		{
			y = (int)round((data->pos_y)) + i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		if ((int)round(x) <= (data->width - 1) && (int)round(y) <= (data->height - 1) && data->map[(int)round(y)][(int)round(x)] != '0')
		{
			return ((double)data->res_y / (sqrtf((data->pos_x - x) * (data->pos_x - x) +
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

	while (x < (double)data->width && y < (double)data->height)
	{
		if ((int)round((data->pos_y - 1)) == (int)round((data->pos_y - 0.5)))
		{
			y = (int)round((data->pos_y - 1)) - i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		else
		{
			y = (int)round((data->pos_y)) - i;
			x = data->pos_x + fabs(y - data->pos_y) / data->vector_y_mod * data->vector_x_mod;
		}
		if ((int)round(x) <= (data->width - 1) && (int)round(y) <= (data->height - 1) && data->map[(int)round(y)][(int)round(x)] != '0')
		{
			return ((double)data->res_y / (sqrtf((data->pos_x - x) * (data->pos_x - x) +
			(data->pos_y - y) * (data->pos_y - y))));
		}
		i++;
	}
	return (0);
}
