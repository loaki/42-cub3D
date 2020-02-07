/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_image.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:28:02 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/07 15:22:07 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_init_win(t_data *data)
{
	if ((data->mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr,
		data->res_x, data->res_y, "marche")) == NULL)
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

int		ft_init_health(t_data *data)
{
	int		k;
	char	*paths[2];

	k = 0;
	paths[0] = "./textures/health/empty.xpm";
	paths[1] = "./textures/health/full.xpm";
	data->life = 100;
	while (k < 2)
	{
		if (!(data->health[k] = malloc(sizeof(t_image))))
			return (EXIT_FAILURE);
		if ((data->health[k]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			paths[k], &data->health[k]->width,
			&data->health[k]->height)) == NULL)
			return (EXIT_FAILURE);
		if ((data->health[k]->addr_ptr =
			mlx_get_data_addr(data->health[k]->img_ptr, &data->health[k]->bpp,
			&data->health[k]->size_l, &data->health[k]->endiant)) == NULL)
			return (EXIT_FAILURE);
		k++;
	}
	return (EXIT_SUCCESS);
}

int		ft_init_textures(t_data *data)
{
	int i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		if (data->t_path[i] != 0)
		{
			if (!(data->tex[i] = malloc(sizeof(t_image))))
				return (EXIT_FAILURE);
			if ((data->tex[i]->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
				data->t_path[i], &data->tex[i]->width,
				&data->tex[i]->height)) == NULL)
				return (EXIT_FAILURE);
			if ((data->tex[i]->addr_ptr =
				mlx_get_data_addr(data->tex[i]->img_ptr, &data->tex[i]->bpp,
				&data->tex[i]->size_l, &data->tex[i]->endiant)) == NULL)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

void	ft_minimapdim(t_data *data)
{
	data->minimap->width = ((double)data->width / (double)(data->res_x) >
	(double)(data->height) / (double)(data->res_y) ?
	(int)(double)data->res_x / 5 : (int)((double)data->width /
	(double)data->height * (double)data->res_y / 5));
	data->minimap->height = ((double)data->width / (double)(data->res_x) >
	(double)(data->height) / (double)(data->res_y) ?
	(int)((double)data->height / (double)data->width *
	(double)data->res_x / 5) : (int)((double)data->res_y / 5));
}

int		ft_init_minimap(t_data *data)
{
	if (!(data->minimap = malloc(sizeof(t_image))))
		return (EXIT_FAILURE);
	if ((double)data->width / (double)(data->res_x) > (double)(data->height) /
		(double)(data->res_y))
	{
		if ((data->minimap->img_ptr = mlx_new_image(data->mlx_ptr,
			(int)(data->res_x / 5), (int)((double)data->height /
			(double)data->width * (double)data->res_x / 5))) == NULL)
			return (EXIT_FAILURE);
	}
	else if ((data->minimap->img_ptr = mlx_new_image(data->mlx_ptr,
		(int)((double)data->width / (double)data->height *
		(double)data->res_y / 5), (int)((double)data->res_y / 5))) == NULL)
		return (EXIT_FAILURE);
	ft_minimapdim(data);
	if ((data->minimap->addr_ptr = mlx_get_data_addr(data->minimap->img_ptr,
		&data->minimap->bpp, &data->minimap->size_l,
		&data->minimap->endiant)) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_init_image(t_data *data)
{
	data->sprite = NULL;
	if (ft_init_win(data))
		return (ft_clearimg(data, 0));
	if (ft_init_view(data))
		return (ft_clearimg(data, 1));
	if (ft_init_gun(data))
		return (ft_clearimg(data, 2));
	if (ft_init_gameover(data))
		return (ft_clearimg(data, 3));
	if (ft_init_health(data))
		return (ft_clearimg(data, 4));
	if (ft_init_textures(data))
		return (ft_clearimg(data, 5));
	if (ft_init_minimap(data))
		return (ft_clearimg(data, 6));
	return (EXIT_SUCCESS);
}
