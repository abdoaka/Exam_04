#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	print_set(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d", tab[i]);
		i++;
		if (i < size)
			printf(" ");
	}
	printf("\n");
}

void	find_subsets(int *tab, int size, int target, int index, int *subset,int subset_size, int current_sum)
{
	if (index == size)
	{
		if (current_sum == target)
			print_set(subset, subset_size);
		return ;
	}
	find_subsets(tab, size, target, index + 1, subset, subset_size,current_sum);
	subset[subset_size] = tab[index];
	find_subsets(tab, size, target, index + 1, subset, subset_size + 1,current_sum + tab[index]);
}

void	powerset(int *tab, int size, int target)
{
	int	*subset;

	subset = malloc(sizeof(int) * size);
	find_subsets(tab, size, target, 0, subset, 0, 0);
	free(subset);
}

int	main(int ac, char **av)
{
	int	target;
	int	size;
	int	*tab;
	int	i;

	if (ac < 3)
		return (1);
	target = atoi(av[1]);
	size = ac - 2;
	tab = malloc(sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		tab[i] = atoi(av[i + 2]);
		i++;
	}
	powerset(tab, size, target);
	free(tab);
	return (0);
}
