/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/19 15:35:26 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_draw(t_data *data)
{
	int x;
	int y;

	x = 0;
	if ((data->img_ptr = mlx_new_image (data->mlx_ptr, data->res_x, data->res_y)) == NULL)
        return (EXIT_FAILURE);
	if ((data->addr_ptr = mlx_get_data_addr (data->img_ptr, &data->bpp, &data->size_l, &data->endiant)) == NULL)
        return (EXIT_FAILURE);
	data->bpp = data->bpp / 8;
	while (x < data->res_y)
	{
		y = 0;
		while (y < data->res_x)
		{
			if (data->view[y][x] == '1')
				*(int *)(data->addr_ptr + ((x * data->res_x + y) * data->bpp)) = data->color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

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
		if (y > (data->res_y / 2 - size / 2) && y < (data->res_y / 2 + size / 2))
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
	if (data->vector_x_mod > 0)
		size_x = ft_size_wall_xp(data, data->vector_x_mod, data->vector_y_mod);
	else 
		size_x = ft_size_wall_xn(data, data->vector_x_mod, data->vector_y_mod);
	if (data->vector_y_mod > 0)
		size_y = ft_size_wall_yp(data, data->vector_x_mod, data->vector_y_mod);
	else 
		size_y = ft_size_wall_yn(data, data->vector_x_mod, data->vector_y_mod);
	size_x = size_x * (double)data->res_y / (double)data->height;
	size_y = size_y * (double)data->res_y / (double)data->height;
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

/*	for (int k = 0; k < data->res_y; k++)
	{
		for (int l = 0; l < data->res_x; l++)
			printf("%c", data->view[l][k]);
		printf("\n");
	}*/
	ft_draw(data);
	free(data->view);
	return (0);
}

int		ft_parse_data(t_data *data, char *line, int i)
{
		data->map[i] = ft_strdup(line);
		data->width = ft_strlen(line);

	/*
	*parse color / res / texture / pos / orientation
	*/
	data->color = 16711680;
	data->res_x = 80;
	data->res_y = 60;
	data->pos_x = 10;
	data->pos_y = 10;
	data->vector_x = 1;
	data->vector_y = 0;
	/*
	*----------
	*/
	return (0);

}
int		ft_parse(t_data *data, char *map)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	if (!(data->map = malloc(2048)))
		return (EXIT_FAILURE);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		ft_parse_data(data, line, i);
		i++;
		free(line);
	}
	ret = get_next_line(fd, &line);
	ft_parse_data(data, line, i);
	data->height = i;
	i++;
	free(line);
	data->map[i] = 0;
	if (ret == -1)
		return (EXIT_FAILURE);
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
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr, data->res_x, data->res_y, "marche")) == NULL)
        return (EXIT_FAILURE);
	if (ft_view(data) != 0)
		return (EXIT_FAILURE);
	mlx_key_hook(data->win_ptr, deal_key, data);
	mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
