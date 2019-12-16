/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:30:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2019/12/16 20:10:50 by jfeuilla         ###   ########.fr       */
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
	while (x != data->width)
	{
		y = 0;
		while (y != data->height)
		{
			if (data->view[x][y] != '0')
				*(int *)(data->addr_ptr + ((x + y * data->height) * data->bpp)) = data->color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

void	ft_rotate(t_pos pos, double angle)
{
	double x;
	double y;

	x = pos->vector_x * cos(angle / (180 / M_PI) - pos->vector_y * sin(angle / (180 / M_PI);
	y = pos->vector_x * sin(angle / (180 / M_PI) + pos->vector_y * cos(angle / (180 / M_PI);
	pos->vector_x_mod = x;
	pos->vector_y_mod = y;
}

int		ft_view(t_data *data, t_pos *pos)
{
	int i;

	i = -res_x / 120;
	if (!(data->view = malloc(sizeof(char*) * (res_x + 1))))
		return (EXIT_FAILURE);
	if (!(*data->view = malloc(sizeof(char) * (res_y + 1))))
		return (EXIT_FAILURE);
	while (i <= res_x / 120)
	{
		ft_rotate(pos, i);
		
		//raycast

		i++;
	}
	ft_draw(data, 
	return (0);
}

int		ft_parse_map(t_data *data, char *map)
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
		i++;
		free(line);
	}
	ret = get_next_line(fd, &line);
	data->map[i] = ft_strdup(line);
	i++;
	free(line);
	data->map[i] = 0;
	/*
	*parse color / res / texture
	*/
	data->color = 16711680;
	data->res_x = 640;
	data->res_y = 480;
	
	if (ret == -1)
		return (EXIT_FAILURE);
	return (0);
}

int main(int ac, char **av)
{
    t_data		*data;
	t_pos		*pos

	if (ac != 2)
		return (EXIT_FAILURE);
	if (!(data = malloc(sizeof(t_data))))
		return (EXIT_FAILURE);
	if (!(pos = malloc(sizeof(t_pos))))
		return (EXIT_FAILURE);
	if (ft_parse_map(data, av[1]) != 0)
		return (EXIT_FAILURE);
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr, data->res_x, data->res_y, "marche pas")) == NULL)
        return (EXIT_FAILURE);
	
	pos->x = 10;
	pos->y = 10;
	pos->vector_x = 0;
	pos->vector_y = 1;
	ft_view(data, pos);


	mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
