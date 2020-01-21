/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:32:52 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/21 18:48:54 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_gun_color(t_data *data, int x, int y, int id)
{	
	return (*(int *)(data->gun[id]->addr_ptr +
	(int)(((y * data->gun[id]->height / data->res_y) * data->gun[id]->width + x * data->gun[id]->width / data->res_x)) *
	data->gun[id]->bpp / 8));
}

void	ft_display_gun(t_data *data)
{
	int		x;
	int		y;
	int		id;
	int		r;

	r = rand();
	y = 0;
	if (data->fire == 0)
		id = 0;
	else if (r <= RAND_MAX / 3 )
		id = 1;
	else if (r <= RAND_MAX / 3 * 2)
		id = 2;
	else
		id = 3;
	while (y < data->res_y)
	{
		x = 0;
		while (x < data->res_x)
		{
			if (ft_gun_color(data, x, y, id) != 0)
				*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
				data->gun[id]->bpp / 8)) = ft_gun_color(data, x, y, id);
			x++;
		}
		y++;
	}	
}
