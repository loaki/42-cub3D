/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:38:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/08 14:43:30 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_error(char *str)
{
	int i;

	i = 0;
	write(1, "Error\n", 6);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
	exit(0);
	return (0);
}

int		ft_success(t_data *data)
{
	ft_clear_lst(data);
	ft_clearimg(data, 6);
	exit(0);
	return (0);
}

int		main(int ac, char **av)
{
	t_data	*data;
	int		save;

	save = 0;
	if (ac == 3 && !ft_strcmp(av[2], "-save"))
		save = 1;
	if ((ac != 2 && save != 1) || ft_mapname(av[1]))
		return (ft_error("invalid argument"));
	if (!(data = malloc(sizeof(t_data))))
		return (ft_error("malloc failed"));
	if (ft_parse(data, av[1]) == EXIT_FAILURE)
		return (ft_error("invalid map"));
	if (ft_init_image(data) == EXIT_FAILURE)
		return (ft_error("image initialisation failed"));
	if (ft_view(data) == EXIT_FAILURE)
		return (ft_error("raycast failed"));
	if (save == 1)
		return (ft_save_bitmap("screen.bmp", data));
	mlx_hook(data->win_ptr, K_PRESS, 0, &key_press, data);
	mlx_hook(data->win_ptr, K_RELEASE, 0, &key_release, data);
	mlx_hook(data->win_ptr, K_EXIT, 0, &ft_success, data);
	mlx_loop_hook(data->mlx_ptr, &ft_update, data);
	mlx_loop(data->mlx_ptr);
	return (EXIT_SUCCESS);
}
