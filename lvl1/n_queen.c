#include <stdio.h>
#include<stdlib.h>
int positive(int a)
{
	if(a < 0)
		a *= -1;
	return a;
}

int is_safe(int *data,int col , int row )
{
	for ( int i =0 ; i < col ; i ++)
	{
		if(data [i] == row || positive (i -col) == positive (data[i] - row))
			return 0;
	}
	return 1;
}
void solve(int *data ,int col ,int max)
{
	if ( col == max)
	{
		for (int i =0; i < max ; i++)
		{
			printf("%d",data[i]);
			if ( i < max - 1)
				printf(" ");
		}
		printf("\n");
		return;
	}
	for(int i =0 ; i < max ; i++)
	{
		if(is_safe(data,col,i))
		{
			data[col] = i ;
			solve(data,col + 1,max);
		}
	}
}
int main ( int ac ,char **av)
{
	if ( ac != 2)
		return 1;
	int n = atoi(av[1]);
	int *board = malloc(sizeof(int) * n );
	solve (board,0,n);
}
