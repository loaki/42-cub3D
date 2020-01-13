/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:03:32 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/01/13 20:44:56 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parse_res(t_data *data, char *line)
{
	int i;

	i = 1;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		data->res_x = data->res_x * 10 + line[i] - '0';
		i++;
	}
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		data->res_y = data->res_y * 10 + line[i] - '0';
		i++;
	}
	if (data->res_x == 0 || data->res_y == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int		ft_parse_color(t_data *data, char *line)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		c = c * 10 + line[i] - '0';
		i++;
	}
	data->color = c * 256 * 256;
	c = 0;
	i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		c = c * 10 + line[i] - '0';
		i++;
	}
	data->color += c * 256;
	c = 0;
	i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		c = c * 10 + line[i] - '0';
		i++;
	}
	data->color += c;
	i++;
	return (EXIT_SUCCESS);
}




void	ft_parse_map(t_data *data, char *line, int i)
{
	int j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' ||
			line[j] == 'W' || line[j] == 'E')
		{
			data->pos_x = j;
			data->pos_y = i;
			data->vector_x = 0;
			data->vector_y = 0;
		}
		if (line[j] == 'N')
			data->vector_y = 1;
		if (line[j] == 'S')
			data->vector_y = -1;
		if (line[j] == 'E')
			data->vector_x = 1;
		if (line[j] == 'W')
			data->vector_x = -1;
		j++;
	}
	data->map[i] = ft_strdup(line);
}

int		ft_parse_texture(t_data *data, char *line, int id)
{
	int i;
	int size;

	i = 2;
	size = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i + size] && line[i + size] != ' ')
		size++;
	if (!(data->t_path[id] = malloc(size + 1)))
		return (EXIT_FAILURE);
	data->t_path[id][size] = 0;
	while (size > 0)
	{
		data->t_path[id][size - 1] = line[size - 1 + i];
		size--;
	}
	return (EXIT_SUCCESS);
}

int		ft_parse_data(t_data *data, char *line, int *i)
{
	if (line[0] >= '0' && line[0] <= '9')
	{
		ft_parse_map(data, line, *i);
		data->width = ft_strlen(line);
		*i = *i + 1;
	}
	if (line[0] == 'R')
		if (ft_parse_res(data, line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'C')
		if (ft_parse_color(data, line) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'N' && line[1] == 'O')
		if (ft_parse_texture(data, line, 0) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'S' && line[1] == 'O')
		if (ft_parse_texture(data, line, 1) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'W' && line[1] == 'E')
		if (ft_parse_texture(data, line, 2) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'E' && line[1] == 'A')
		if (ft_parse_texture(data, line, 3) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		ft_parse_data(data, line, &i);
		free(line);
	}
	ret = get_next_line(fd, &line);
	ft_parse_data(data, line, &i);
	data->height = i;
	free(line);
	data->map[i] = 0;
	if (ret == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
