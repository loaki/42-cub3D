/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/17 14:41:15 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_draw(t_data *data)
{
	int x;
	int y;

	x = 0;
	if ((data->img_ptr = mlx_new_image (data->mlx_ptr, data->width, data->height)) == NULL)
        return (EXIT_FAILURE);
	if ((data->addr_ptr = mlx_get_data_addr (data->img_ptr, &data->bpp, &data->size_l, &data->endiant)) == NULL)
        return (EXIT_FAILURE);
	data->bpp /= 8;
	while (x < 1/*data->height*/)
	{
		y = 0;
		while (y < data->width)
		{
			if (data->view[x][y] != '0')
				*(int *)(data->addr_ptr + ((x * data->width + y) * data->bpp)) = data->color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

void	ft_rotate(t_pos *pos, double angle)
{
	double x;
	double y;

	x = pos->vector_x * cos(angle / (180 / M_PI)) + pos->vector_y * sin(angle / (180 / M_PI));
	y = -pos->vector_x * sin(angle / (180 / M_PI)) + pos->vector_y * cos(angle / (180 / M_PI));
	pos->vector_x_mod = x;
	pos->vector_y_mod = y;
}

void	ft_fill_view(t_data *data, int x, double size)
{
	int y;

	y = 0;
	write(1, "-----new-----\n", 14);
	while (y < data->res_y)
	{
		write (1, "?", 1);
		if (y > (data->res_y / 2 - size / 2) && y < (data->res_y / 2 + size / 2))
		{
			write (1, "\n-----", 6);
			data->view[x][y] = '1';
			write (1, "ok\n", 3);
		}
		else
		{
			write (1, "\n+++++", 6);
			data->view[x][y] = '0';
			write (1, "ok\n", 3);
		}
		write(1, "ok\n", 3);
		y++;
	}
	data->view[x][y] = 0;
}

void	ft_raycast(t_data *data, t_pos *pos, int i)
{
	double size_x;
	double size_y;

	if (pos->vector_x_mod > 0)
		size_x = ft_size_wall_xp(data, pos, pos->vector_x_mod, pos->vector_y_mod);
	else 
		size_x = ft_size_wall_xn(data, pos, pos->vector_x_mod, pos->vector_y_mod);
	if (pos->vector_y_mod > 0)
		size_y = ft_size_wall_yp(data, pos, pos->vector_x_mod, pos->vector_y_mod);
	else 
		size_y = ft_size_wall_yn(data, pos, pos->vector_x_mod, pos->vector_y_mod);
	if (size_x > size_y)
		ft_fill_view(data, i, size_x);
	else
		ft_fill_view(data, i, size_y);
}

int		ft_view(t_data *data, t_pos *pos)
{
	int		i;
	double	angle;

	i = 0;
	angle = -30;
	if (!(data->view = malloc(sizeof(char*) * (data->res_x + 1))))
		return (EXIT_FAILURE);
	if (!(*data->view = malloc(sizeof(char) * (data->res_y + 1))))
		return (EXIT_FAILURE);
	data->view[data->res_x] = 0;
//	while (angle < 30)
	while (i < 1)
	{
		ft_rotate(pos, angle);
		ft_raycast(data, pos, i);
		i++;
		angle += data->res_x / 60;
	}
	ft_draw(data);
	return (0);
}

int		ft_parse_map(t_data *data, t_pos *pos, char *map)
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
		data->map[i] = ft_strdup(line);
		data->width = ft_strlen(line);
		i++;
		free(line);
	}
	ret = get_next_line(fd, &line);
	data->map[i] = ft_strdup(line);
	data->height = i;
	i++;
	free(line);
	data->map[i] = 0;
	/*
	*parse color / res / texture / pos / orientation
	*/
	data->color = 16711680;
	data->res_x = 300;
	data->res_y = 70;
	pos->x = 10;
	pos->y = 10;
	pos->vector_x = 1;
	pos->vector_y = 0;

	if (ret == -1)
		return (EXIT_FAILURE);
	return (0);
}

int main(int ac, char **av)
{
    t_data		*data;
	t_pos		*pos;

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!(data = malloc(sizeof(t_data))))
		return (EXIT_FAILURE);
	if (!(pos = malloc(sizeof(t_pos))))
		return (EXIT_FAILURE);
	if (ft_parse_map(data, pos, av[1]) != 0)
		return (EXIT_FAILURE);
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr, data->res_x, data->res_y, "marche pas")) == NULL)
        return (EXIT_FAILURE);
	if (ft_view(data, pos) != 0)
        return (EXIT_FAILURE);
	mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
