/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:20:47 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/11 15:49:52 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_move_f(t_data *data)
{
	data->pos_x += 0.1 * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 || 
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x -= 0.1 * data->vector_x;
	data->pos_y -= 0.1 * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y += 0.1 * data->vector_y;
//	ft_info(data);
	return (ft_view(data));
}

int		ft_move_b(t_data *data)
{
	data->pos_x -= 0.1 * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x += 0.1 * data->vector_x;
	data->pos_y += 0.1 * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y -= 0.1 * data->vector_y;
//	ft_info(data);
	return (ft_view(data));
}

int		ft_move_r(t_data *data)
{
	data->pos_x += 0.1 * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x -= 0.1 * data->vector_y;
	data->pos_y += 0.1 * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y -= 0.1 * data->vector_x;
//	ft_info(data);
	return (ft_view(data));
}

int		ft_move_l(t_data *data)
{
	data->pos_x -= 0.1 * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x += 0.1 * data->vector_y;
	data->pos_y -= 0.1 * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y += 0.1 * data->vector_x;
//	ft_info(data);
	return (ft_view(data));
}

int		ft_rotate_l(t_data *data)
{
	ft_rotate(data, -2);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
//	ft_info(data);
	return (ft_view(data));
}

int		ft_rotate_r(t_data *data)
{
	ft_rotate(data, 2);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
//	ft_info(data);
	return (ft_view(data));
}

void	ft_info(t_data *data)
{
	printf("\n----------\npos_x = |%f| pos_y = |%f|\n", data->pos_x, data->pos_y);
	printf("res_x = %d\nres_y = %d\nvector_x = %f\nvector_y = %f\nwidth = %d\nheight = %d\nc = %c\n",
	data->res_x, data->res_y, data->vector_x, data->vector_y, data->width, data->height, data->map[(int)data->pos_y][(int)data->pos_x]);
}
