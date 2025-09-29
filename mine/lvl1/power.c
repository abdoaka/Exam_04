#include <stdio.h>
#include <stdlib.h>

void print_set(int *tab , int size )
{
	for(int i = 0 ; i < size ; i++)
	{
		printf("%d",tab[i]);
		if(i < size -1)
			printf(" ");
	}
	printf("\n");
}
void solve(int *array ,int  target , int index , int size , int *new_array , int subset_size , int current_some)
{
	if(index == size )
	{
		if(current_some == target)
			print_set(new_array,subset_size);
	}
 solve( array ,   target ,  index +1,  size ,  new_array ,  subset_size   ,  current_some);
	array[index] = new_array[subset_size];
 solve( array ,   target ,  index ,  size ,  new_array ,  subset_size + 1  ,  current_some + array[index]);

}
void powerset(int *tab ,int target , int size )
{
	int *new_array = malloc(size);
	solve(tab ,target,0,size,new_array,0,0);
}
int main(int ac , char *av)
{
	int target = atoi(av[1]);
	int size = ac -2;
	int *tab = malloc(size);
	for(int i = 0 ; i < size ; i++)
		tab[i] = atoi(av[i+2]);
	powerset(tab,target,size);
}
