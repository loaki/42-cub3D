/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/13 21:00:09 by jfeuilla         ###   ########.fr       */
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
		ft_size_wall_xp(data, data->vector_x_mod, data->vector_y_mod);
	else if (data->vector_x_mod < -0.0000001)
		ft_size_wall_xn(data, data->vector_x_mod, data->vector_y_mod);
	if (data->vector_y_mod > 0.0000001)
		ft_size_wall_yp(data, data->vector_x_mod, data->vector_y_mod);
	else if (data->vector_y_mod < -0.0000001)
		ft_size_wall_yn(data, data->vector_x_mod, data->vector_y_mod);
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
	while (angle < 30)
	{
		ft_rotate(data, angle);
		if (ft_raycast(data, i) != 0)
			return (EXIT_FAILURE);
		i++;
		angle += 60 / (double)data->res_x;
	}
//	ft_info(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
	data->view->img_ptr, 0, 0);
	ft_minimap(data);
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
	return (EXIT_SUCCESS);
}

int		ft_update(t_data *data)
{
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
	if (data->esc == 1)
	{
		free(data);
		exit(0);
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_data	*data;
	if (ac != 2)
		return (EXIT_FAILURE);
	if (!(data = malloc(sizeof(t_data))))
		return (EXIT_FAILURE);
	write(1, "...\n", 4);
	if (ft_parse(data, av[1]) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	write(1, "parsing.....ok\n", 15);
	if (ft_init_image(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	write(1, "init image..ok\n", 15);
	if (ft_view(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	write(1, "display.....ok\n", 15);
	mlx_hook(data->win_ptr, K_PRESS, 0, &key_press, data);
	mlx_hook(data->win_ptr, K_RELEASE, 0, &key_release, data);
	mlx_loop_hook(data->mlx_ptr, &ft_update, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
