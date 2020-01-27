/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gun.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:32:52 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/27 16:17:14 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_gun_color(t_data *data, int x, int y, int id)
{
	return (*(int *)(data->gun[id]->addr_ptr +
	(int)(((y * data->gun[id]->height / data->res_y) * data->gun[id]->width +
	x * data->gun[id]->width / data->res_x)) * data->gun[id]->bpp / 8));
}

void	ft_shot(t_data *data)
{
	t_list	*lst;
	double	a;
	double	b;
	double	c;

	if (data->sprite == NULL)
		return ;
	lst = data->sprite;
	while (lst->next)
	{
		a = (((-data->pos_y) + data->vector_y) - (-data->pos_y))
				/ ((data->pos_x + data->vector_x) - data->pos_x);
		b = -1;
		c = (-data->pos_y) - a * data->pos_x;
		if ((fabs(a * lst->x + b * (-lst->y) + c) / sqrt(a * a + b * b)) < 0.5)
			data->map[(int)lst->y][(int)lst->x] = '0';
		lst = lst->next;
	}
	a = (((-data->pos_y) + data->vector_y) - (-data->pos_y))
			/ ((data->pos_x + data->vector_x) - data->pos_x);
	b = -1;
	c = (-data->pos_y) - a * data->pos_x;
	if ((fabs(a * lst->x + b * (-lst->y) + c) / sqrt(a * a + b * b)) < 0.5)
		data->map[(int)lst->y][(int)lst->x] = '0';
}

void	ft_display_gun(t_data *data)
{
	int		x;
	int		y;
	int		id;
	int		r;

	y = 0;
	r = rand();
	id = (r <= RAND_MAX ? 3 : 0);
	id = (r <= RAND_MAX / 3 * 2 ? 2 : id);
	id = (r <= RAND_MAX / 3 ? 1 : id);
	id = (data->fire == 0 ? 0 : id);
	while (y < data->res_y)
	{
		x = 0;
		while (x < data->res_x)
		{
			if (ft_gun_color(data, x, y, id) != 0)
				*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
				data->view->bpp / 8)) = ft_gun_color(data, x, y, id);
			x++;
		}
		y++;
	}
	if (id > 0)
		ft_shot(data);
}
