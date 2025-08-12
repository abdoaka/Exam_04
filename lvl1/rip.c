#include <stdio.h>
#include <stdlib.h>

int		balance = 0;

int	ft_balance(char *str)
{
	int	unclosed;
	int	unopened;
	int	i;

	unclosed = 0;
	unopened = 0;
	i = 0;
	while (i < str[i])
	{
		if (str[i] == '(')
			unclosed++;
		else if (str[i] == ')')
		{
			if (unclosed > 0)
				unclosed--;
			else
				unopened++;
		}
		i++;
	}
	return (unclosed + unopened);
}

void	ft_backtrack(char *str, int changes, int pos)
{
	int		i;
	char	c;

	if (balance == changes && !ft_balance(str))
	{
		puts(str);
		return ;
	}
	i = pos;
	while (str[i])
	{
		if (str[i] == ')' || str[i] == '(')
		{
			c = str[i];
			str[i] = ' ';
			ft_backtrack(str, changes + 1, i + 1);
			str[i] = c;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	balance = ft_balance(av[1]);
	ft_backtrack(av[1], 0, 0);
	return (0);
}
