/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:20:47 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/22 16:00:11 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_move_f(t_data *data)
{
	data->pos_x += SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 || 
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x -= SPEED * data->vector_x;
	data->pos_y -= SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y += SPEED * data->vector_y;
}

void	ft_move_b(t_data *data)
{
	data->pos_x -= SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x += SPEED * data->vector_x;
	data->pos_y += SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y -= SPEED * data->vector_y;
}

void	ft_move_r(t_data *data)
{
	data->pos_x += SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x -= SPEED * data->vector_y;
	data->pos_y += SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y -= SPEED * data->vector_x;
}

void	ft_move_l(t_data *data)
{
	data->pos_x -= SPEED * data->vector_y;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_x += SPEED * data->vector_y;
	data->pos_y -= SPEED * data->vector_x;
	if (data->pos_y > (data->height - 1) || data->pos_x > (data->width - 1) ||
		data->pos_y < 0 || data->pos_x < 0 ||
		data->map[(int)data->pos_y][(int)data->pos_x] == '1')
		data->pos_y += SPEED * data->vector_x;
}

void	ft_rotate_l(t_data *data)
{
	ft_rotate(data, -5);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
}

void	ft_rotate_r(t_data *data)
{
	ft_rotate(data, 5);
	data->vector_x = data->vector_x_mod;
	data->vector_y = data->vector_y_mod;
}

void	ft_info(t_data *data)
{
	write(1, "info...", 7);
	printf("\n----------\npos_x = |%f| pos_y = |%f|\n", data->pos_x, data->pos_y);
	printf("res_x = %d\nres_y = %d\nvector_x = %f\nvector_y = %f\nwidth = %d\nheight = %d\nc = %c\n",
	data->res_x, data->res_y, data->vector_x, data->vector_y, data->width, data->height, data->map[(int)data->pos_y][(int)data->pos_x]);
	
	if (data->sprite)
	{
		t_list *lst;
		lst = data->sprite;
		if (lst)
		{
			printf("s = %12f%12f%12d%12f\n", lst->x, lst->y, lst->col, lst->dist_vector);
			while (lst->next)
			{
				lst = lst->next;
				printf("s = %12f%12f%12d%12f\n", lst->x, lst->y, lst->col, lst->dist_vector);
			}
		}
	}
}
