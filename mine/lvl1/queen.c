#include <stdio.h>
#include <stdlib.h>

int positive(int a)
{
	if(a < 0 )
		a *= -1;
	return a;
}
int check(int *board , int col , int max )
{
	for(int i =0 ; i < col ; i++)
	{
		if(board[i] == max || positive(i - col ) == positive(board[i] - max))
			return 0;
	}
	return 1;
}
void solve(int *board , int col , int max)
{
	if(col == max)
	{
		for(int i =0 ; i < max ; i++)
		{
			printf("%d",board[i]);
			if(i < max - 1)
				printf(" ");
		}
		printf("\n");
	}
	for(int i =0 ; i < max ; i++)
	{
		if(check(board , col , i))
		{
			board[col] = i ;
			solve(board,col + 1 , max);
		}
	}
}
int main ( int ac , char **av)
{
	int n = atoi(av[1]);
	int *board = malloc(n);
	solve(board,0,n);
}
