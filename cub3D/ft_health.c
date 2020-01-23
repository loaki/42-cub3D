/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_health.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:59:49 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/23 16:25:01 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_health_color(t_data *data, int x, int y, int id)
{	
	return (*(int *)(data->health[id]->addr_ptr +
	(int)((((y - data->res_y / 50) * data->health[id]->height / (5 * data->res_y / 50 - data->res_y / 50)) * data->health[id]->width + (x - data->res_x / 4) * data->health[id]->width / (3 * data->res_x / 4 - data->res_x / 4))) *
	data->health[id]->bpp / 8));
}

void	ft_display_health(t_data *data)
{
	int x;
	int y;
	int id;

	y = data->res_y / 50;
	id = 0;
	while (id < 2)
	{
		while (y < 5 * data->res_y / 50)
		{
			x = data->res_x / 4;
			while (x < 3 * data->res_x / 4)
			{
				if (id == 0 || x < ((double)data->life / 100 * (3 * data->res_x / 4)))
					if (ft_health_color(data, x, y, id) != 0)
					{
						*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
						data->view->bpp / 8)) = ft_health_color(data, x, y, id);
					}
				x++;
			}
			y++;
		}
		y = data->res_y / 50;
		id++;
	}
}
			
