/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_image2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 16:40:50 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/10 17:17:01 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_init_win(t_data *data)
{
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr,
		data->res_x, data->res_y, "cub3D")) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_init_view(t_data *data)
{
	if (!(data->view = malloc(sizeof(t_image))))
		return (EXIT_FAILURE);
	if ((data->view->img_ptr = mlx_new_image(data->mlx_ptr, data->res_x,
		data->res_y)) == NULL)
		return (EXIT_FAILURE);
	if ((data->view->addr_ptr = mlx_get_data_addr(data->view->img_ptr,
		&data->view->bpp, &data->view->size_l, &data->view->endiant)) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_init_gun(t_data *data)
{
	int		j;
	char	*path[4];

	j = 0;
	path[0] = "./textures/gun/gun.xpm";
	path[1] = "./textures/gun/shot1.xpm";
	path[2] = "./textures/gun/shot2.xpm";
	path[3] = "./textures/gun/shot3.xpm";
	while (j < 4)
	{
		if (!(data->gun[j] = malloc(sizeof(t_image))))
			return (EXIT_FAILURE);
		if ((data->gun[j]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			path[j], &data->gun[j]->width,
			&data->gun[j]->height)) == NULL)
			return (EXIT_FAILURE);
		if ((data->gun[j]->addr_ptr = mlx_get_data_addr(data->gun[j]->img_ptr,
			&data->gun[j]->bpp,
			&data->gun[j]->size_l, &data->gun[j]->endiant)) == NULL)
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int		ft_init_gameover(t_data *data)
{
	if (!(data->gameover = malloc(sizeof(t_image))))
		return (EXIT_FAILURE);
	if ((data->gameover->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		"./textures/gameover/gameover.xpm", &data->gameover->width,
		&data->gameover->height)) == NULL)
		return (EXIT_FAILURE);
	if ((data->gameover->addr_ptr = mlx_get_data_addr(data->gameover->img_ptr,
		&data->gameover->bpp,
		&data->gameover->size_l, &data->gameover->endiant)) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
