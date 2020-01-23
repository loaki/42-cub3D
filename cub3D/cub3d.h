/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:26:05 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/23 13:27:57 by jfeuilla         ###   ########.fr       */
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
# include <time.h>
# include "mlx.h"
# include "get_next_line.h"

# define K_ESC			53
# define K_W			13
# define K_S			1
# define K_A			0
# define K_D			2
# define K_RIGHT		124
# define K_LEFT			123
# define K_SPACE		49
# define K_PRESS		2
# define K_RELEASE		3
# define NB_TEXTURES	12
# define SPEED			0.1

#endif

typedef	struct	s_image
{
	void			*img_ptr;
	void			*addr_ptr;
	int				bpp;
	int				size_l;
	int				endiant;
	int				width;
	int				height;
}				t_image;

typedef struct 		s_list
{
	double			x;
	double			y;
	double			dist;
	double			dist_vector;
	int				col;
	int				id;
	struct s_list	*next;
}					t_list;

typedef struct	s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			**map;
	int				width;
	int				height;
	t_image			*view;
	t_image			*minimap;
	t_image			*gun[4];
	t_image			*health[2];
	t_image			*gameover;
	t_image			*tex[NB_TEXTURES];
	char			*t_path[NB_TEXTURES];
	t_list			*sprite;
	unsigned int	ceil;
	unsigned int	floor;
	int				res_x;
	int				res_y;
	double			pos_x;
	double			pos_y;
	double			vector_x;
	double			vector_y;
	double			vector_x_mod;
	double			vector_y_mod;
	double			wall_size;
	double			wall_x;
	double			wall_y;
	int				move_f;
	int				move_b;
	int				move_r;
	int				move_l;
	int				rotate_r;
	int				rotate_l;
	int				esc;
	int				fire;
	int				life;
}				t_data;


void			ft_rotate(t_data *data, double angle);
int				ft_raycast(t_data *data, int i);
int				ft_view(t_data *data);
int				key_press(int key, t_data *data);
int				key_release(int key, t_data *data);
int				ft_update(t_data *data);

int				ft_init_image(t_data *data);

int				ft_texture_color(t_data *data, int y, int id);
void			ft_draw_col(t_data *data, int x, char wall);
int				ft_minimap(t_data *data);
int				ft_gameover_color(t_data *data, int x, int y);
void			ft_gameover(t_data *data);

void			ft_size_wall_xp(t_data *data, double x, double y, int col);
void			ft_size_wall_xn(t_data *data, double x, double y, int col);
void			ft_size_wall_yp(t_data *data, double x, double y, int col);
void			ft_size_wall_yn(t_data *data, double x, double y, int col);

void			ft_move_f(t_data *data);
void			ft_move_b(t_data *data);
void			ft_move_l(t_data *data);
void			ft_move_r(t_data *data);
void			ft_rotate_l(t_data *data);
void			ft_rotate_r(t_data *data);
void			ft_info(t_data *data);

int				ft_parse_res(t_data *data, char *line);
int				ft_parse_ceil(t_data *data, char *line);
int				ft_parse_floor(t_data *data, char *line);
void			ft_parse_map(t_data *data, char *line, int i);
int				ft_parse_texture(t_data *data, char *line, int id);
int				ft_parse_data(t_data *data, char *line, int *i);
void			ft_init_path(t_data *data);
int				ft_parse(t_data *data, char *map);

int				ft_save_sprite(t_data *data, double x, double y, int i);
void			ft_clear_lst(t_data *data);
int				ft_sprite_color(t_data *data, t_list *lst, int y);
void			ft_display_sprite(t_data *data, t_list *lst, int col);
double			ft_dist_sprite(t_data *data, double x, double y);

int				ft_gun_color(t_data *data, int x, int y, int id);
void			ft_shot(t_data *data);
void			ft_display_gun(t_data *data);

int				ft_health_color(t_data *data, int x, int y, int id);
void			ft_display_health(t_data *data);
/*
gcc  -framework OpenGL -framework AppKit main.c libmlx.a get_next_line.c get_next_line_utils.c ft_size_wall.c ft_init_image.c
*/
