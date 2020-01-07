/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 12:58:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/07 13:01:52 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_draw(t_data *data)
{
	int x;
	int y;

	x = 0;
	if ((data->img_ptr = mlx_new_image(data->mlx_ptr, data->res_x,
		data->res_y)) == NULL)
		return (EXIT_FAILURE);
	if ((data->addr_ptr = mlx_get_data_addr(data->img_ptr, &data->bpp,
		&data->size_l, &data->endiant)) == NULL)
		return (EXIT_FAILURE);
	while (x < data->res_y)
	{
		y = 0;
		while (y < data->res_x)
		{
			if (data->view[y][x] == '1')
				*(int *)(data->addr_ptr + ((x * data->res_x + y) *
				data->bpp / 8)) = data->color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->img_ptr, 0, 0);
	return (0);
}
