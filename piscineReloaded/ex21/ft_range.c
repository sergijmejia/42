#include <stdlib.h>
//#include <stdio.h>

int	*ft_range(int min, int max)
{
	int	*range;
	int	*aux;

	if (min >= max)
		return (NULL);

	range = (int *) malloc ((max - min + 1) * sizeof(int));
	aux = range;
	while (min < max)
	{
		*aux = min;
		min++;
		aux++;
	}
	*aux = '\0';
	return (range);
}
/*
void	ft_print_numbers(int *num)
{
	while (*num != '\0')
	{
		printf("%d ", *num);
		num++;
	}
	printf("\n");
}

int	main(int argc, char *argv[])
{
	int	min;
	int	max;
	int	*range;
	
	if (argc != 3)
		return (1);
	min = atoi(argv[1]);
	max = atoi(argv[2]);
	range = ft_range(min, max);
	ft_print_numbers(range);
}
*/
