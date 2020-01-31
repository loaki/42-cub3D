#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_truc(int i)
{
	(void)i;
	write(1, "ah\n", 3);
	return (0);
}
int main()
{
	int i =	1;
	int j = 1;
	if (!ft_truc(i) || !ft_truc(j))
	{
		write(1, "ok\n", 3);
	}
}
