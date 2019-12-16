#include "get_next_line.h"
#include <fcntl.h>
#include <math.h>
#include "mlx.h"
#include <stdio.h>

static int ft_len(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int main(int ac, char **av)
{
	int fd;
	char *line;
	int ret;
	int i = 0;
	int j = 0;
	char map[20][20];

	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		j = 0;
		while (j < ft_len(line))
		{
			map[i][j] = line[j];
			j++;
		}
		map[i][j] = 0;
		i++;
	}
	*map[i] = 0;
	for (int h = 0; h <20; h++)
	{
		for (int o = 0; o < 20; o++)
			printf("%c", map[h][o]);
		printf("\n");
	}
	int k = 0;
	int l = j;
	int dh = 0;
	int dw = 0;
	int dist = 0;
	int height = 0;
	void *p;
	void *ptr;
	void *ptr2;
	int *bpp;

	while(k < j)
	{
		l = j;
		while (l >= 0)
		{
			if (map[l][k] == '1')
			{
				dh = abs(l - 15);
				dw = abs(k - 10);
				dist = sqrt(dh * dh + dw * dw);
				height = 60/dist;	
				printf("%d, ", height);
				i = 0;
				break;
			}
			l--;
		}
		k++;
	}
}




