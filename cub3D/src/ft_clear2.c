/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:53:31 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/08 18:56:33 by jfeuilla         ###   ########.fr       */
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
