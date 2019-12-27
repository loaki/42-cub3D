
#include "cub3d.h"

int ft_res(t_data *data, char *line)
{
	int i = 1;
	int f = 1;

	while (line[i] < '0' && line[i] > '9' && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		data->res_x += f * (line[i] - '0');
		f *= 10;
		i++;
	}
	f = 1;
	while (line[i] < '0' && line[i] > '9' && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		data->res_y += f * (line[i] - '0');
		f *= 10;
		i++;
	}
	if (data->res_x == 0 || data->res_y == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

