#include "cub3d.h"

int	ft_draw(t_data *data)
{
	int x;
	int y;

	x = 0;
	if ((data->img_ptr = mlx_new_image (data->mlx_ptr, data->res_x, data->res_y)) == NULL)
        return (EXIT_FAILURE);
	if ((data->addr_ptr = mlx_get_data_addr (data->img_ptr, &data->bpp, &data->size_l, &data->endiant)) == NULL)
        return (EXIT_FAILURE);
	data->bpp = data->bpp / 8;
	while (x < data->res_y)
	{
		y = 0;
		while (y < data->res_x)
		{
			if (data->view[y][x] == '1')
				*(int *)(data->addr_ptr + ((x * data->res_x + y) * data->bpp)) = data->color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	return (0);
}

