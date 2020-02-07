/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:20:47 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/07 16:36:35 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_f(t_data *data)
{
	data->pos_x += SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_x -= SPEED * data->vector_x;
	data->pos_y -= SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_y += SPEED * data->vector_y;
}

void	ft_move_b(t_data *data)
{
	data->pos_x -= SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_x += SPEED * data->vector_x;
	data->pos_y += SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_y -= SPEED * data->vector_y;
}

void	ft_move_r(t_data *data)
{
	data->pos_x += SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_x -= SPEED * data->vector_y;
	data->pos_y += SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_y -= SPEED * data->vector_x;
}

void	ft_move_l(t_data *data)
{
	data->pos_x -= SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_x += SPEED * data->vector_y;
	data->pos_y -= SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1' ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '3')
		data->pos_y += SPEED * data->vector_x;
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
