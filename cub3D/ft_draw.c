/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/07 16:39:20 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_texture_color(t_data *data, int y, int id)
{
	if (id == 0)
		return (*(int *)(data->tex[id]->addr_ptr +
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) *
		(double)data->tex[id]->height / (double)data->wall_size) *
		(double)data->tex[id]->width + (int)((double)fmod(data->wall_x, 1) *
		(double)data->tex[id]->width)) * 4));
	else if (id == 1)
		return (*(int *)(data->tex[id]->addr_ptr +
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) *
		(double)data->tex[id]->height / (double)data->wall_size) *
		(double)data->tex[id]->width + (int)((double)(1 - fmod(data->wall_x, 1))
		* (double)data->tex[id]->width)) * 4));
	else if (id == 2)
		return (*(int *)(data->tex[id]->addr_ptr +
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) *
		(double)data->tex[id]->height / (double)data->wall_size) *
		(double)data->tex[id]->width + (int)((double)(1 - fmod(data->wall_y, 1))
		* (double)data->tex[id]->width)) * 4));
	else if (id == 3)
		return (*(int *)(data->tex[id]->addr_ptr +
		(int)((int)((y - ((double)data->res_y - data->wall_size) / 2) *
		(double)data->tex[id]->height / (double)data->wall_size) *
		(double)data->tex[id]->width + (int)((double)fmod(data->wall_y, 1) *
		(double)data->tex[id]->width)) * 4));
		return (0);
}

void	ft_draw_col(t_data *data, int x, char wall)
{
	int y;
	int id;

	y = 0;
	if (wall == 'y')
		id = (data->vector_y_mod > 0 ? 0 : 1);
	else if (wall == 'x')
		id = (data->vector_x_mod > 0 ? 3 : 2);
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
		y++;
	}
}

void	ft_minimap(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->minimap->height)
	{
		x = 0;
		while (x < data->minimap->width)
		{
			*(int *)(data->minimap->addr_ptr + (((y * data->minimap->width + x))
			* data->minimap->bpp / 8)) = (data->map[(int)(y * data->height /
			data->minimap->height)][(int)(x * data->width /
			data->minimap->width)] == '1' ? 6579300 : 0);
			x++;
		}
		y++;
	}
	*(int *)(data->minimap->addr_ptr + (((int)(data->pos_y *
	data->minimap->height / data->height) * data->minimap->width +
	(int)(data->pos_x * data->minimap->width / data->width)) *
	data->minimap->bpp / 8)) = 16711680;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->minimap->img_ptr, 5, 5);
}

int		ft_gameover_color(t_data *data, int x, int y)
{
	return (*(int *)(data->gameover->addr_ptr +
	(int)((((y - data->res_y / 3) * data->gameover->height / (2 * data->res_y
	/ 3 - data->res_y / 3)) * data->gameover->width + x * data->gameover->width
	/ data->res_x)) * data->gameover->bpp / 8));
}

int		ft_gameover(t_data *data)
{
	int x;
	int y;

	y = data->res_y / 3;
	data->life--;
	while (y < 2 * data->res_y / 3)
	{
		x = 0;
		while (x < data->res_x)
		{
			if (ft_gameover_color(data, x, y) != 0)
				*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
				data->view->bpp / 8)) = ft_gameover_color(data, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->view->img_ptr, 0, 0);
	return (0);
}
