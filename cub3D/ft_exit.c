/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 19:38:20 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/04 19:38:58 by jfeuilla         ###   ########.fr       */
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
	system("leaks a.out");
	exit(0);
	return (0);
}

int		ft_success(t_data *data)
{
	ft_clear_lst(data);
	ft_clearimg(data, 6);
	system("leaks a.out");
	exit(0);
	return (0);
}
