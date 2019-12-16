#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "mlx.h"

typedef struct    data_s
{
    void        *mlx_ptr;
    void        *win_ptr;
	void		*img_ptr;
	void		*addr_ptr;

	int			bpp;
	int			size_l;
	int			endiant;
}                 data_t;

int main(void)
{
    data_t        *data;
	
	data = malloc(sizeof(data_t));
   if ((data->mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr, 640, 480, "marche pas")) == NULL)
        return (EXIT_FAILURE);
	if ((data->img_ptr = mlx_new_image (data->mlx_ptr, 640, 480)) == NULL)
        return (EXIT_FAILURE);
	if ((data->addr_ptr = mlx_get_data_addr (data->img_ptr, &data->bpp, &data->size_l, &data->endiant)) == NULL)
        return (EXIT_FAILURE);
	data->bpp /= 8;
	*(int *)(data->addr_ptr + ((50 + 100 * 480) * data->bpp)) = 16711680;
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 0, 0);
	mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
