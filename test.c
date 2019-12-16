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
}                 data_t;

int main(void)
{
    data_t        *data;
	int bpp;
	int size_l;
	int endiant;

	
	data = malloc(sizeof (data_t));
   if ((data->mlx_ptr = mlx_init()) == NULL)
        return (EXIT_FAILURE);
	if ((data->win_ptr = mlx_new_window(data->mlx_ptr, 640, 480, "marche pas")) == NULL)
        return (EXIT_FAILURE);
	if ((data->img_ptr = mlx_new_image (data->mlx_ptr, 640, 480)) == NULL)
        return (EXIT_FAILURE);
	mlx_pixel_put (data->mlx_ptr, data->win_ptr, 300, 300, 16711680);
	if ((data->addr_ptr = mlx_get_data_addr (data->img_ptr, &bpp, &size_l, &endiant)) == NULL)
        return (EXIT_FAILURE);
	printf("|%d|\n", bpp);
	printf("|%d|\n", size_l);
	printf("|%d|\n", endiant);
	*((int *)(data->addr_ptr + (50 + 100*480 / bpp/8))) = 427819008;
	mlx_put_image_to_window (data->mlx_ptr, data->win_ptr, data->img_ptr, 640, 480);
	mlx_loop(data->mlx_ptr);
    return (EXIT_SUCCESS);
}
