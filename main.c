/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/20 15:26:32 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//------------------
void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb < 0)
	{
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
		ft_putchar(nb + '0');
}

//-------------------

void	ft_rotate(t_data *data, double angle)
{
	double x;
	double y;

	x = data->vector_x * cos(angle / (180 / M_PI)) + data->vector_y * sin(angle / (180 / M_PI));
	y = -data->vector_x * sin(angle / (180 / M_PI)) + data->vector_y * cos(angle / (180 / M_PI));
	data->vector_x_mod = x;
	data->vector_y_mod = y;
}

void	ft_fill_view(t_data *data, int x, double size)
{
	int y;

	y = 0;
	while (y < data->res_y)
	{
		if (y >= round(((double)data->res_y / 2 - size / 2)) && y <= round(((double)data->res_y / 2 + size / 2)))
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
	printf("x=|%f| y=|%f vx=|%f| vy=|%f|\n", data->pos_x, data->pos_y, data->vector_x_mod, data->vector_y_mod);
	if (data->vector_x_mod > 0.0000001)
		size_x = ft_size_wall_xp(data, data->vector_x_mod, data->vector_y_mod);
	else if (data->vector_x_mod < -0.0000001)
		size_x = ft_size_wall_xn(data, data->vector_x_mod, data->vector_y_mod);
	if (data->vector_y_mod > 0.0000001)
		size_y = ft_size_wall_yp(data, data->vector_x_mod, data->vector_y_mod);
	else if (data->vector_y_mod < -0.0000001)
		size_y = ft_size_wall_yn(data, data->vector_x_mod, data->vector_y_mod);
	if (size_x > size_y)
	{
		printf("sx=|%f|\n", size_x);
		ft_fill_view(data, i, size_x);
	}
	else
	{
		printf("sy=|%f|\n", size_x);
		ft_fill_view(data, i, size_y);
	}
	return (0);
}

int		ft_view(t_data *data)
{
	int		i;
	double	angle;

	i = 0;
	angle = -30;
//	angle = 0;
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
	for (int k = 0; k < data->res_y; k++)
	{
		for (int l = 0; l < data->res_x; l++)
			printf("%c", data->view[l][k]);
		printf("\n");
	}
//	ft_draw(data);
	free(data->view);
	return (0);
}

int		deal_key(int key, t_data *data)
{
	if (key == K_W)
		ft_move_f(data);
	if (key == K_S)
		ft_move_b(data);
	if (key == K_A)
		ft_move_l(data);
	if (key == K_D)
		ft_move_r(data);
	return (1);
}

int main(int ac, char **av)
{
    t_data		*data;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!(data = malloc(sizeof(t_data))))
		return (EXIT_FAILURE);
	if (ft_parse(data, av[1]) != 0)
		return (EXIT_FAILURE);

	printf("x = %d\ny = %d\nposx = %f\nposy = %f\nvx = %f\nvy = %f\nw = %d\nh = %d\n", data->res_x, data->res_y, data->pos_x, data->pos_y, data->vector_x, data->vector_y, data->width, data->height);
	for (int i = 0; i < data->height; i++)
	{
		for (int j = 0; j < data->width; j++)
			printf("%c", data->map[i][j]);
		printf("\n");
	}

//	if ((data->mlx_ptr = mlx_init()) == NULL)
//		return (EXIT_FAILURE);
//	if ((data->win_ptr = mlx_new_window(data->mlx_ptr, data->res_x, data->res_y, "marche")) == NULL)
//      return (EXIT_FAILURE);

	if (ft_view(data) != 0)
		return (EXIT_FAILURE);

//	mlx_key_hook(data->win_ptr, deal_key, data);
//	mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
