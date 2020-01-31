/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/31 13:40:55 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_rotate(t_data *data, double angle)
{
	double x;
	double y;

	x = data->vector_x * cos(angle / (180 / M_PI)) + data->vector_y *
	sin(angle / (180 / M_PI));
	y = -data->vector_x * sin(angle / (180 / M_PI)) + data->vector_y *
	cos(angle / (180 / M_PI));
	data->vector_x_mod = x;
	data->vector_y_mod = y;
}

int		ft_raycast(t_data *data, int i)
{
	data->wall_size = 0;
	if (data->vector_x_mod > 0.0000001)
		ft_size_wall_xp(data, data->vector_x_mod, data->vector_y_mod, i);
	else if (data->vector_x_mod < -0.0000001)
		ft_size_wall_xn(data, data->vector_x_mod, data->vector_y_mod, i);
	if (data->vector_y_mod > 0.0000001)
		ft_size_wall_yp(data, data->vector_x_mod, data->vector_y_mod, i);
	else if (data->vector_y_mod < -0.0000001)
		ft_size_wall_yn(data, data->vector_x_mod, data->vector_y_mod, i);
	if (data->wall_x == (int)(data->wall_x))
		ft_draw_col(data, i, 'x');
	else
		ft_draw_col(data, i, 'y');
	return (EXIT_SUCCESS);
}

int		ft_view(t_data *data)
{
	int		i;
	double	angle;

	i = 0;
	angle = -30;
	ft_clear_lst(data);
	data->enemy = 0;
	while (angle < 30)
	{
		ft_rotate(data, angle);
		if (ft_raycast(data, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ft_display_sprite(data, data->sprite, i);
		i++;
		angle += 60 / (double)data->res_x;
	}
	i = rand();
	if (i < RAND_MAX / 4)
		data->life -= data->enemy;
	ft_display_gun(data);
	ft_display_health(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->view->img_ptr, 0, 0);
	ft_minimap(data);
	ft_info(data);
	return (EXIT_SUCCESS);
}

int		key_press(int key, t_data *data)
{
	if (key == K_W)
		data->move_f = 1;
	if (key == K_S)
		data->move_b = 1;
	if (key == K_D)
		data->move_r = 1;
	if (key == K_A)
		data->move_l = 1;
	if (key == K_RIGHT)
		data->rotate_r = 1;
	if (key == K_LEFT)
		data->rotate_l = 1;
	if (key == K_SPACE)
		data->fire = 1;
	if (key == K_ESC)
		data->esc = 1;
	return (EXIT_SUCCESS);
}

int		key_release(int key, t_data *data)
{
	if (key == K_W)
		data->move_f = 0;
	if (key == K_S)
		data->move_b = 0;
	if (key == K_D)
		data->move_r = 0;
	if (key == K_A)
		data->move_l = 0;
	if (key == K_RIGHT)
		data->rotate_r = 0;
	if (key == K_LEFT)
		data->rotate_l = 0;
	if (key == K_SPACE)
		data->fire = 0;
	return (EXIT_SUCCESS);
}

int		ft_update(t_data *data)
{
	if (data->esc == 1)
		ft_success(data);
	if (data->life <= 40)
		return (ft_gameover(data));
	if (data->move_f == 1)
		ft_move_f(data);
	if (data->move_b == 1)
		ft_move_b(data);
	if (data->move_r == 1)
		ft_move_r(data);
	if (data->move_l == 1)
		ft_move_l(data);
	if (data->rotate_r == 1)
		ft_rotate_r(data);
	if (data->rotate_l == 1)
		ft_rotate_l(data);
	ft_view(data);
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_data	*data;
	int		save;

	if (ac == 3 && !ft_strcmp(av[2], "-save"))
		save = 1;
	if (ac != 2 && save != 1)
		return (ft_error("invalid argument"));
	write(1, "1\n", 2);
	if (!(data = malloc(sizeof(t_data))))
		return (ft_error("malloc failed"));
	write(1, "1\n", 2);
	if (ft_parse(data, av[1]) == EXIT_FAILURE)
		return (ft_error("invalid map"));
	write(1, "1\n", 2);
	if (ft_init_image(data) == EXIT_FAILURE)
		return (ft_error("image initialisation failed"));
	write(1, "1\n", 2);
	if (ft_view(data) == EXIT_FAILURE)
		return (ft_error("raycast failed"));
	write(1, "1\n", 2);
	mlx_hook(data->win_ptr, K_PRESS, 0, &key_press, data);
	mlx_hook(data->win_ptr, K_RELEASE, 0, &key_release, data);
	mlx_hook(data->win_ptr, K_EXIT, 0, &ft_success, data);
	mlx_loop_hook(data->mlx_ptr, &ft_update, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
