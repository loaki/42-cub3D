/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 13:07:01 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/14 17:00:43 by jfeuilla         ###   ########.fr       */
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

int		ft_save_sprite(t_data *data, double x, double y, int i)
{
	t_list	*lst;
	t_list	*new;

	if (!(new = malloc(sizeof(t_list))))
		return (EXIT_FAILURE);
	new->x = (int)x + 0.5;
	new->y = (int)y + 0.5;
	new->dist = sqrtf((new->x - data->pos_x) * (new->x - data->pos_x)
	+ (new->y - data->pos_y) * (new->y - data->pos_y));
	new->col = i;
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
			if (lst->x != new->x && lst->y != new->y)
			{
				if (lst->next)
					new->next = lst->next;
				lst->next = new;
			}
		}
	}
	return (EXIT_SUCCESS);
}

int		ft_sprite_color(t_data *data, int x, int y, int id, double size)
{
	return (*(int *)(data->tex[id]->addr_ptr +
	(int)((y - (double)data->res_y / 2 - (double)size) * (double)data->tex[id]->height / (double)size) * data->tex[id]->width
	+ (int)((x - (double)data->res_x / 2 - (double)size) * (double)data->tex[id]->width / (double)size)) * 4);
}

void	ft_display_sprite(t_data *data, t_list *lst)
{
	int x;
	int y;

	x = 0;
	if (lst)
	{
		while (x < data->res_x)
		{
			y = 0;
			if (x >= (double)lst->col - (double)data->res_y / lst->dist && 
				x <= (double)lst->col + (double)data->res_y / lst->dist)
			{
				while (y < data->res_y)
				{
					if (y >= (double)data->res_y / 2 - (double)data->res_y / lst->dist / 2 && 
						y <= (double)data->res_y / 2 + (double)data->res_y / lst->dist / 2)
					{
			//			if (ft_sprite_color(data, x, y, 4, (double)data->res_y / lst->dist / 2)
			//				!= 0)
							*(int *)(data->view->addr_ptr + ((y * data->res_x + x) *
							data->view->bpp / 8)) = ft_sprite_color(data, x, y, 3, (double)data->res_y / lst->dist / 2);
					}
					y++;
				}
			}
			x++;
		}
		if (lst->next)
			ft_display_sprite(data, lst->next);
	}
}
