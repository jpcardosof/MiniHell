#include "minishell.h"

void	ft_pwd(char **str)
{
	int		pid;
	int		status;
	char	dir[1024];

	(void) str;
	getcwd(dir, (sizeof(char) * 1024));
	pid = fork();
	if (pid == 0)
	{
		if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
			exit_child();
		dup2(data()->fd[0][1], STDOUT_FILENO);
		printf("%s\n", dir);
		child_exit();
	}
	else
	{
		waitpid(pid, &status, 0);
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
	}
}

void	ft_pwd_exec(char **str)
{
	char	dir[1024];

	(void) str;
	getcwd(dir, (sizeof(char) * 1024));
	printf("%s\n", dir);
}
