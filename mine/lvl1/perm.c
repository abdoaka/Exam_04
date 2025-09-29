#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void sorted(char *str)
{
	char tmp;
	for(int i = 0; str[i] ; i++)
	{
		for(int j = i +1 ; str[j] ; j++)
		{
			if(str[i] > str[j] )
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
		}
	}
}
void solve(char *str , char *result, int *used , int start , int end)
{
	if(start == end)
	{
		for(int i = 0 ; result[i] ; i++)
			write(1,&result[i],1);
		write(1,"\n",1);
	}
	for(int i = 0 ; i < end ; i++)
	{
		if(used[i])
			continue;
		used[i] = 1;
		result[start] = str[i];
		solve(str,result,used,start + 1 , end);
		used[i] = 0;
	}
}

int main(int ac , char **av)
{
	int len = strlen(av[1]);
	char *result = malloc(len + 1);
	int *used = calloc(len,sizeof(int));
	sorted(av[1]);
	solve(av[1],result,used,0,len);
}
