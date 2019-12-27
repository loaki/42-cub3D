/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:05 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 17:14:04 by jfeuilla         ###   ########.fr       */
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
//# include "mlx.h"
# include "get_next_line.h"

# define K_ESC		53
# define K_W		13
# define K_S		1
# define K_A		0
# define K_D		2

# endif

typedef struct	s_data
{
    void    	    *mlx_ptr;
    void    	    *win_ptr;
	void			*img_ptr;
	void			*addr_ptr;
	char			**map;
	char			**view;
	int				width;
	int				height;
	int				bpp;
	int				size_l;
	int				endiant;
	unsigned int	color;
	int				res_x;
	int				res_y;
	double			pos_x;
	double			pos_y;
	double			vector_x;
	double			vector_y;
	double			vector_x_mod;
	double			vector_y_mod;
}				t_data;

void	ft_rotate(t_data *data, double angle);
int		ft_view(t_data *data);

double	ft_size_wall_xp(t_data *data, double x, double y);
double	ft_size_wall_xn(t_data *data, double x, double y);
double	ft_size_wall_yp(t_data *data, double x, double y);
double	ft_size_wall_yn(t_data *data, double x, double y);

void	ft_move_f(t_data *data);
void	ft_move_b(t_data *data);
void	ft_move_l(t_data *data);
void	ft_move_r(t_data *data);

int		ft_parse_res(t_data *data, char *line);
void	ft_parse_map(t_data *data, char *line, int i);
int		ft_parse_data(t_data *data, char *line, int i);
int		ft_parse(t_data *data, char *map);

/*
*--------------
*/
//gcc  -framework OpenGL -framework AppKit main.c libmlx.a get_next_line.c get_next_line_utils.c ft_size_wall.c
void ft_info(t_data *data);
