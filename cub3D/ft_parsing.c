/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfeuilla <jfeuilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:03:32 by jfeuilla          #+#    #+#             */
/*   Updated: 2020/02/03 19:38:46 by jfeuilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	ft_atoi(char *str, int *i)
{
	unsigned int	c;

	c = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		c = c * 10 + str[*i] - '0';
		*i += 1;
	}
	return (c);
}

char			*ft_linedup(char *str)
{
	int i;
	int len;
	char *ret;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			len ++;
		i++;
	}
	if (!(ret = malloc(len + 1)))
		return (0);
	while (i >= 0)
	{
		if (str[i] != ' ')
		{
			ret[len] = str[i];
			len--;
		}
		i--;
	}
	return (ret);
}

int				ft_parse_res(t_data *data, char *line)
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
	if (data->res_x <= 0 || data->res_y <= 0 ||
		data->res_x > 2560 || data->res_y > 1440)
	{
		data->res_x = 2560;
		data->res_y = 1440;
	}
	return (EXIT_SUCCESS);
}

int				ft_parse_ceil(t_data *data, char *line)
{
	int i;
	int c;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	c = ft_atoi(line, &i);
	data->ceil = c * 256 * 256;
	i++;
	c = ft_atoi(line, &i);
	data->ceil += c * 256;
	i++;
	c = ft_atoi(line, &i);
	data->ceil += c;
	return (EXIT_SUCCESS);
}

int				ft_parse_floor(t_data *data, char *line)
{
	int i;
	int c;

	i = 0;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	c = ft_atoi(line, &i);
	data->floor = c * 256 * 256;
	i++;
	c = ft_atoi(line, &i);
	data->floor += c * 256;
	i++;
	c = ft_atoi(line, &i);
	data->floor += c;
	return (EXIT_SUCCESS);
}

int			ft_parse_map(t_data *data, char *line, int *i)
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
				return (ft_clearmap(data));
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
		if (ft_parse_map(data, line, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'R' && line[1] == ' ')
		ft_parse_res(data, line);
	if (line[0] == 'C' && line[1] == ' ')
		ft_parse_ceil(data, line);
	if (line[0] == 'F' && line[1] == ' ')
		ft_parse_floor(data, line);
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		if (ft_parse_texture(data, line, 0) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		if (ft_parse_texture(data, line, 1) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		if (ft_parse_texture(data, line, 2) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		if (ft_parse_texture(data, line, 3) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	if (line[0] == 'S' && ((line[1] >= '0' && line[1] <= '9')
		|| line[1] == ' '))
		if (ft_parse_texture(data, line, 4) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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
	ret = get_next_line(fd, &line);
	if (ft_parse_data(data, line, &i))
	{
		free(line);
		return (ft_clearmap(data));
	}
	data->height = i;
	free(line);
	if (ft_checkmap(data) || ft_checkpath(data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
