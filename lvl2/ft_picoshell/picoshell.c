#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handle_child_process(char **cmd, int prev_fd, int *pipefd,
		char **next_cmd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			exit(1);
		close(prev_fd);
	}
	if (next_cmd)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipefd[1]);
	}
	execvp(cmd[0], cmd);
	exit(1);
}

static void	handle_parent_cleanup(int *prev_fd, int *pipefd, char **next_cmd)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (next_cmd)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

static int	wait_for_all_children(void)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	while (wait(&status) != -1)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_code = 1;
	}
	return (exit_code);
}

int	picoshell(char **cmds[])
{
	pid_t	pid;
	int		pipefd[2];
	int		prev_fd;
	int		i;

	prev_fd = -1;
	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1] && pipe(pipefd))
			return (1);
		pid = fork();
		if (pid == -1)
		{
			if (cmds[i + 1])
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			return (1);
		}
		if (pid == 0)
		{
			handle_child_process(cmds[i], prev_fd, pipefd, cmds[i + 1]);
		}
		handle_parent_cleanup(&prev_fd, pipefd, cmds[i + 1]);
		i++;
	}
	return (wait_for_all_children());
}
