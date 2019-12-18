/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 12:20:47 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/18 14:31:52 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_f(t_pos *pos)
{
	pos->x += pos->vector_x;
	pos->y -= pos->vector_y;
	ft_info(pos);
}
void	ft_move_b(t_pos *pos)
{
	pos->x -= pos->vector_x;
	pos->y += pos->vector_y;
	ft_info(pos);
	
}
void	ft_move_l(t_pos *pos)
{
	ft_rotate(pos, -10);
	pos->vector_x = pos->vector_x_mod;
	pos->vector_y = pos->vector_y_mod;
	ft_info(pos);
	
}
void	ft_move_r(t_pos *pos)
{
	ft_rotate(pos, 10);
	pos->vector_x = pos->vector_x_mod;
	pos->vector_y = pos->vector_y_mod;
	ft_info(pos);
}

void ft_info(t_pos *pos)
{
	printf("\n----------\nx = |%f| y = |%f|\n", pos->x, pos->y);
	printf("vect x = |%f| vect y = |%f|\n", pos->vector_x, pos->vector_y);
}
