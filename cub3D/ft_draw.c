/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/13 15:29:33 by jfeuilla         ###   ########.fr       */
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
void	ft_draw_col(t_data *data, int x, double size)
{
	int y;

	y = 0;
	while (y < data->res_y)
	{
		if (y >= round(((double)data->res_y / 2 - size / 2)) &&
			y <= round(((double)data->res_y / 2 + size / 2)))
			*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
			data->view->bpp / 8)) = data->color;
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
