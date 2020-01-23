/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:07:01 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/23 14:56:05 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clear_lst(t_data *data)
{
	t_list	*tmp;
	t_list	*lst;

	lst = data->sprite;
	if (lst)
	{
		while (lst->next)
		{
			tmp = lst->next;
			free(lst);
			lst = tmp;
		}
		free(lst);
	}
	data->sprite = NULL;	
}

double	ft_dist_sprite(t_data *data, double x, double y)
{
	double a;
	double b;
	double c;

	y *= -1;
	a = (((-data->pos_y) + data->vector_y_mod) - (-data->pos_y))
			/ ((data->pos_x + data->vector_x_mod) - data->pos_x);
	b = -1;
	c = (-data->pos_y) - a * data->pos_x;
	double r = data->vector_x_mod * data->vector_y_mod;
	double r1 = data->vector_x_mod * (y + data->pos_y);
	double r2 = (data->pos_x + data->vector_x_mod - x) * data->vector_y_mod;
	if (r - r1 - r2 > 0)
		return (-1 * (fabs(a * x + b * y + c) / sqrt(a * a + b * b)));
	return (fabs(a * x + b * y + c) / sqrt(a * a + b * b));
}

int		ft_save_sprite(t_data *data, double x, double y, int col)
{
	t_list	*lst;
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (EXIT_FAILURE);
	new->x = (int)x + 0.5;
	new->y = (int)y + 0.5;
	new->dist = sqrtf((new->x - data->pos_x) * (new->x - data->pos_x)
	+ (new->y - data->pos_y) * (new->y - data->pos_y));
	new->col = col;
	new->dist_vector = ft_dist_sprite(data, new->x, new->y);
	new->id = data->map[(int)y][(int)x] - '0' + 2;
	new->next = NULL;
	if (data->sprite == NULL)
		data->sprite = new;
	else
	{
		lst = data->sprite;
		if (new->dist > lst->dist)
		{
			new->next = lst;
			data->sprite = new;
		}
		else
		{
			while (lst->next && lst->next->dist >= new->dist)
				lst = lst->next;
			if (lst->x == new->x && lst->y == new->y)
			{
				lst->col = new->col;
				lst->dist_vector = new->dist_vector;
			}
			else
			{
				if (lst->next)
					new->next = lst->next;
				lst->next = new;
			}
		}
	}
	return (EXIT_SUCCESS);
}

int		ft_sprite_color(t_data *data, t_list *lst, int y)
{
	int		x;
	double 	size;

	x = (int)((lst->dist_vector + 0.5) * (double)data->tex[lst->id]->width);
	size = (double)data->res_y / lst->dist;
	return (*(int *)(data->tex[lst->id]->addr_ptr +
	(int)((int)((y - ((double)data->res_y - size) / 2) * (double)data->tex[lst->id]->height / size) * (double)data->tex[lst->id]->width
	+ (int)((double)x)) * data->tex[lst->id]->bpp / 8));
}

void	ft_display_sprite(t_data *data, t_list *lst, int col)
{
	int y;

	if (lst)
	{
		y = 0;
		while (y < data->res_y)
		{
			if (y >= (double)data->res_y / 2 - (double)data->res_y / lst->dist / 2 && 
				y <= (double)data->res_y / 2 + (double)data->res_y / lst->dist / 2 &&
				lst->col == col && ((double)data->res_y / lst->dist > data->wall_size) &&
				lst->dist_vector > -0.5 && lst->dist_vector < 0.5)
				if (ft_sprite_color(data, lst, y) != 0)
				{
					if (lst->id == 4)
						data->enemy = 0.5;
					*(int *)(data->view->addr_ptr + ((y * data->res_x + col) *
					data->tex[lst->id]->bpp / 8)) = ft_sprite_color(data, lst, y);
				}
			y++;
		}
		if (lst->next)
			ft_display_sprite(data, lst->next, col);
	}
}
