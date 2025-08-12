#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_popen(const char *file, char *const argv[], char type)
{
	int	fds[2];
	pid_t pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return (-1);
	if (pipe(fds) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	if (pid == 0)
	{
		if (type == 'r')
		{
			if (dup2(fds[1], STDOUT_FILENO) == -1)
				exit(1);
		}
		else
		{
			if (dup2(fds[0], STDIN_FILENO) == -1)
				exit(1);
		}
		close(fds[0]);
		close(fds[1]);
		execvp(file, argv);
		exit(1);
	}
	if (type == 'r')
	{
		close(fds[1]);
		return fds[0];
	}
	else
	{
		close(fds[0]);
		return fds[1];
	}
}
int main ( int ac , char **av)
{

int fd = ft_popen("ls", (char*[]){"ls", NULL}, 'r');


char line[100];
read(fd, line, 100);
printf("Files: %s", line);
}
