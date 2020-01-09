/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/09 16:34:01 by jfeuilla         ###   ########.fr       */
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

void	ft_fill_view(t_data *data, int x, double size)
{
	int y;

	y = 0;
	while (y < data->res_y)
	{
		if (y >= round(((double)data->res_y / 2 - size / 2)) &&
			y <= round(((double)data->res_y / 2 + size / 2)))
			data->view[x][y] = '1';
		else
			data->view[x][y] = '0';
		y++;
	}
	data->view[x][y] = 0;
}

int		ft_raycast(t_data *data, int i)
{
	double size_x;
	double size_y;

	if (!(data->view[i] = malloc(data->res_y + 1)))
		return (EXIT_FAILURE);
	size_x = 0;
	size_y = 0;
	if (data->vector_x_mod > 0.0000001)
		size_x = ft_size_wall_xp(data, data->vector_x_mod, data->vector_y_mod);
	else if (data->vector_x_mod < -0.0000001)
		size_x = ft_size_wall_xn(data, data->vector_x_mod, data->vector_y_mod);
	if (data->vector_y_mod > 0.0000001)
		size_y = ft_size_wall_yp(data, data->vector_x_mod, data->vector_y_mod);
	else if (data->vector_y_mod < -0.0000001)
		size_y = ft_size_wall_yn(data, data->vector_x_mod, data->vector_y_mod);
	if (size_x > size_y)
		ft_fill_view(data, i, size_x);
	else
		ft_fill_view(data, i, size_y);
	return (0);
}

int		ft_view(t_data *data)
{
	int		i;
	double	angle;

	i = 0;
	angle = -30;
	if (!(data->view = (char **)malloc(sizeof(char*) * (data->res_x + 1))))
		return (EXIT_FAILURE);
	data->view[data->res_x] = 0;
	while (angle < 30)
	{
		ft_rotate(data, angle);
		if (ft_raycast(data, i) != 0)
			return (EXIT_FAILURE);
		i++;
		angle += 60 / (double)data->res_x;
	}
	ft_draw(data);
	return (0);
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
	return (0);
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
	return (0);
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
		exit(0);
	return (0);
}

int		main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!(data = malloc(sizeof(t_data))))
		return (EXIT_FAILURE);
	if (ft_parse(data, av[1]) != 0)
		return (EXIT_FAILURE);
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr,
		data->res_x, data->res_y, "marche")) == NULL)
		return (EXIT_FAILURE);
	if (ft_view(data) != 0)
		return (EXIT_FAILURE);
	mlx_hook(data->win_ptr, K_PRESS, 0, &key_press, data);
	mlx_hook(data->win_ptr, K_RELEASE, 0, &key_release, data);
	mlx_loop_hook(data->mlx_ptr, &ft_update, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
