/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 14:15:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/08 14:43:09 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_int_to_char(char *str, int nb)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		str[i] = (unsigned char)(nb >> (i * 8));
		i++;
	}
}

int				ft_save_bitmap(char *filename, t_data *data)
{
	int		i;
	int		fd;
	char	header[54];

	i = 0;
	while (i < 54)
	{
		header[i] = (unsigned char)0;
		i++;
	}
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	ft_int_to_char(header + 2, data->res_x * data->res_y * 4 + 54);
	ft_int_to_char(header + 10, 54);
	ft_int_to_char(header + 14, 40);
	ft_int_to_char(header + 18, data->res_x);
	ft_int_to_char(header + 22, data->res_y);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	fd = open(filename, O_RDWR | O_CREAT, 0666);
	write(fd, header, 54);
	ft_bitmap_image(data, fd);
	close(fd);
	return (EXIT_SUCCESS);
}

void			ft_bitmap_image(t_data *data, int fd)
{
	int				x;
	int				y;
	int				temp;
	unsigned char	color[3];
	int				*ptr;

	ptr = (int *)data->view->addr_ptr;
	y = data->res_y - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < data->res_x)
		{
			temp = ptr[x + y * data->res_x];
			color[0] = temp % 256;
			temp /= 256;
			color[1] = temp % 256;
			temp /= 256;
			color[2] = temp % 256;
			write(fd, &color, sizeof(color));
			x++;
		}
		y--;
	}
}
