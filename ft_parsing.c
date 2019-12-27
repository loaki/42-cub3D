
#include "cub3d.h"

int ft_parse_res(t_data *data, char *line)
{
	int i;
	int f;

	i = 1;
	f = 1;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		data->res_x = data->res_x * f + line[i] - '0';
		f *= 10;
		i++;
	}
	f = 1;
	while ((line[i] < '0' || line[i] > '9') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		data->res_y = data->res_y * f + line[i] - '0';
		f *= 10;
		i++;
	}
	if (data->res_x == 0 || data->res_y == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_parse_map(t_data *data, char *line, int i)
{
	int j;

	j = 0;
	while (line[j])
	{
		if (line[j] == 'N' || line[j] == 'S' || line[j] == 'W' || line[j] == 'E')
		{
			data->pos_x = j;
			data->pos_y = i;
		}
		if (line[j] == 'N' || line[j] == 'S')
			data->vector_x = 0;
		if (line[j] == 'E' || line[j] == 'W')
			data->vector_y = 0;
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
	/*
	*parse color / res / texture / pos / orientation
	*/
	data->color = 16711680;
	/*
	*----------
	*/
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
	return (0);
}
