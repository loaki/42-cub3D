#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

double	ft_dist_sprite(double x, double y, double px, double py, double vx, double vy)
{
	double a;
	double b;
	double c;

	y *= -1;
	a = (-py) - ((-py) + vy);
	b = (px + vx) - px;
	c = (px * ((-py) + vy) - 
		(px + vx) * (-py));
/*	if (b == 0)
	{
		if (x < px)
			return (fabs(a * x + b * y + c) / sqrt(a * a + b * b));
		else
			return (-1 * fabs(a * x + b * y + c) / sqrt(a * a + b * b));
	}*/
	printf("%f\n", (vx * ((-py) - y) - vy * (px - x)));
//	if ((vx * ((-py) - y) - vy * (px - x)) >= 0)
		return (fabs(a * x + b * y + c) / sqrt(a * a + b * b));
//	return (-1 * fabs(a * x + b * y + c) / sqrt(a * a + b * b));
}

int main()
{
	printf("%f\n", ft_dist_sprite(7.5, 7.5, 10.7, 10.3, -0.63, 0.77));
}
