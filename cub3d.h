/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:05 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/17 14:41:19 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"

# endif

typedef struct	s_data
{
    void        *mlx_ptr;
    void        *win_ptr;
	void		*img_ptr;
	void		*addr_ptr;
	char		**map;
	char		**view;
	int			width;
	int			height;
	int			bpp;
	int			size_l;
	int			endiant;
	int			color;
	int			res_x;
	int			res_y;
}				t_data;

typedef struct	s_pos
{
	double		x;
	double		y;
	double		vector_x;
	double		vector_y;
	double		vector_x_mod;
	double		vector_y_mod;
}				t_pos;


double	ft_size_wall_xp(t_data *data, t_pos *pos, double x, double y);
double	ft_size_wall_xn(t_data *data, t_pos *pos, double x, double y);
double	ft_size_wall_yp(t_data *data, t_pos *pos, double x, double y);
double	ft_size_wall_yn(t_data *data, t_pos *pos, double x, double y);
