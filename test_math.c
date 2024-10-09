#include <stdio.h>
#include <math.h>
#include "./headers/cub3d.h"

// int	main(void)
// {
// 	printf("tan(60deg) = %f\n", tan(PI/3));
// }

int	main(void)
{
	double	value = 179.999999;
	printf("%i\n", (int)value);
	printf("%f\n", rounded_nearest_nb(0));
}