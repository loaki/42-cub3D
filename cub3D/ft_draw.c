/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/21 18:51:22 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
//---------------------------
#include <time.h>

void delay(double mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
//----------------------------

int		ft_texture_color(t_data *data, int y, int id)
{
	if (id == 0)
		return (*(int *)(data->tex[id]->addr_ptr + 
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) * (double)data->tex[id]->height / (double)data->wall_size) * (double)data->tex[id]->width +
		(int)((double)fmod(data->wall_x, 1) * (double)data->tex[id]->width)) * 4));
	if (id == 1)
		return (*(int *)(data->tex[id]->addr_ptr + 
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) * (double)data->tex[id]->height / (double)data->wall_size) * (double)data->tex[id]->width +
		(int)((double)(1 - fmod(data->wall_x, 1)) * (double)data->tex[id]->width)) * 4));
	if (id == 2)
		return (*(int *)(data->tex[id]->addr_ptr + 
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) * (double)data->tex[id]->height / (double)data->wall_size) * (double)data->tex[id]->width +
		(int)((double)(1 - fmod(data->wall_y, 1)) * (double)data->tex[id]->width)) * 4));
	if (id == 3)
		return (*(int *)(data->tex[id]->addr_ptr + 
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) * (double)data->tex[id]->height / (double)data->wall_size) * (double)data->tex[id]->width +
		(int)((double)fmod(data->wall_y, 1) * (double)data->tex[id]->width)) * 4));
	return (0);
}

void	ft_draw_col(t_data *data, int x, char wall)
{
	int y;
	int id;

	y = 0;
	if (wall == 'y' && data->vector_y_mod > 0)
		id = 0;
	else if (wall == 'y' && data->vector_y_mod < 0)
		id = 1;
	else if (wall == 'x' && data->vector_x_mod < 0)
		id = 2;
	else if (wall == 'x' && data->vector_x_mod > 0)
		id = 3;
	while (y < data->res_y)
	{
		if (y < ((double)data->res_y / 2 - data->wall_size / 2))
			*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
			data->view->bpp / 8)) = data->ceil; 
		else if (y > ((double)data->res_y / 2 + data->wall_size / 2))
			*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
			data->view->bpp / 8)) = data->floor; 
		else if (y >= ((double)data->res_y / 2 - data->wall_size / 2) &&
			y <= ((double)data->res_y / 2 + data->wall_size / 2))
			*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
			data->view->bpp / 8)) = ft_texture_color(data, y, id); 
		else
			*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
			data->view->bpp / 8)) = 0;
		y++;
	}
}


int	ft_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->minimap->height)
	{
		x = 0;
		while (x < data->minimap->width)
		{
			if (data->map[(int)(y * data->height / data->minimap->height)]
				[(int)(x * data->width / data->minimap->width)] == '1')
				*(int *)(data->minimap->addr_ptr + (((y * data->minimap->width + x)) *
				data->minimap->bpp / 8)) = 6579300;
			else
				*(int *)(data->minimap->addr_ptr + (((y * data->minimap->width + x)) *
				data->minimap->bpp / 8)) = 0;
			x++;
		}
		y++;
	}
	*(int *)(data->minimap->addr_ptr + (((int)(data->pos_y * data->minimap->height / data->height) * data->minimap->width +
	(int)(data->pos_x * data->minimap->width / data->width)) * data->minimap->bpp / 8)) = 16711680;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->minimap->img_ptr, 5, 5);
	return (0);
}
