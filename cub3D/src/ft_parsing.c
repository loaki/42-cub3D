/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:03:32 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/07 16:51:11 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_parse_map(t_data *data, char *line, int *i)
{
	int j;

	j = 0;
	data->map[*i] = ft_linedup(line);
	data->map[*i + 1] = 0;
	while (data->map[*i][j])
	{
		if (data->map[*i][j] == 'N' || data->map[*i][j] == 'S' ||
			data->map[*i][j] == 'W' || data->map[*i][j] == 'E')
		{
			if (data->pos_x != 0 || data->pos_y != 0)
				return (EXIT_FAILURE);
			data->pos_x = j + 0.5;
			data->pos_y = *i + 0.5;
			data->vector_x = (data->map[*i][j] == 'E' ? 1 : 0);
			data->vector_x = (data->map[*i][j] == 'W' ? -1 : data->vector_x);
			data->vector_y = (data->map[*i][j] == 'N' ? 1 : 0);
			data->vector_y = (data->map[*i][j] == 'S' ? -1 : data->vector_y);
		}
		j++;
	}
	data->width = j;
	*i = *i + 1;
	return (EXIT_SUCCESS);
}

int				ft_parse_texture(t_data *data, char *line, int id)
{
	int i;
	int size;

	i = 2;
	size = 0;
	if (line[1] >= '0' && line[1] <= '9')
		id = line[1] - '0' + 2;
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

int				ft_parse_data(t_data *data, char *line, int *i)
{
	if (line[0] >= '0' && line[0] <= '9')
		return (ft_parse_map(data, line, i));
	if (line[0] == 'R' && line[1] == ' ')
		return (ft_parse_res(data, line));
	if (line[0] == 'C' && line[1] == ' ')
		return (ft_parse_ceil(data, line));
	if (line[0] == 'F' && line[1] == ' ')
		return (ft_parse_floor(data, line));
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (ft_parse_texture(data, line, 0));
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (ft_parse_texture(data, line, 1));
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (ft_parse_texture(data, line, 2));
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (ft_parse_texture(data, line, 3));
	if (line[0] == 'S' && ((line[1] >= '0' && line[1] <= '9')
		|| line[1] == ' '))
		return (ft_parse_texture(data, line, 4));
	return (EXIT_SUCCESS);
}

void			ft_init_parse(t_data *data)
{
	int i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		data->t_path[i] = 0;
		i++;
	}
	data->map[0] = 0;
	data->pos_x = 0;
	data->pos_y = 0;
}

int				ft_parse(t_data *data, char *map)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	if (!(data->map = malloc(2048)))
		return (EXIT_FAILURE);
	ft_init_parse(data);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_parse_data(data, line, &i))
		{
			free(line);
			return (ft_clearmap(data));
		}
		free(line);
	}
	data->height = i;
	free(line);
	if (ft_checkmap(data) || ft_checkpath(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
