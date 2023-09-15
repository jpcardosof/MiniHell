#include "minishell.h"

void	swap_fd(void)
{
	if (data()->fd[0][0] != STDIN_FILENO)
		close(data()->fd[0][0]);
	if (data()->fd[0][1] != STDOUT_FILENO)
		close(data()->fd[0][1]);
	data()->fd[0][0] = data()->fd[1][0];
	data()->fd[0][1] = data()->fd[1][1];
	data()->fd[1][0] = STDIN_FILENO;
	data()->fd[1][1] = STDOUT_FILENO;
}

void	generate_fds(void)
{
	data()->fd[0][0] = STDIN_FILENO;
	data()->fd[0][1] = STDOUT_FILENO;
	data()->fd[1][0] = STDIN_FILENO;
	data()->fd[1][1] = STDOUT_FILENO;
}

void	child_exec(void)
{
	char	*path;

	if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
	{
		swap_fd();
		swap_fd();
		free_all();
		exit(1);
	}
	path = check_path(data()->cmds[data()->curr_cmd][0]);
	dup2(data()->fd[0][0], STDIN_FILENO);
	dup2(data()->fd[0][1], STDOUT_FILENO);
	if (execve(path, data()->cmds[data()->curr_cmd], data()->env_p) == -1)
	{
		free(path);
		exec_error();
	}
}

void	execute_cmd(void)
{
	int	pid;
	int	status;
	int	tmp_curr;

	tmp_curr = data()->curr_cmd + 1;
	if (data()->cmds[tmp_curr] != NULL && is_spc(data()->cmds[tmp_curr][0]))
		tmp_curr = fd_check(tmp_curr);
	pid = fork();
	if (pid == 0)
		child_exec();
	else
	{
		waitpid(pid, &status, 0);
		swap_fd();
		if (status > 0)
			data()->error = status / 256;
		else
			data()->error = 0;
		data()->curr_cmd = tmp_curr;
	}
}

void	cmd_to_exec(void)
{
	data()->cmds = generate_cmd();
	generate_fds();
	data()->curr_cmd = 0;
	if (is_valid_cmd(-1))
	{
		free_triple_ptr(data()->cmds);
		return ;
	}
	while (data()->cmds && data()->cmds[data()->curr_cmd] != NULL)
	{
		if (data()->cmds[data()->curr_cmd] != NULL \
		&& is_spc(data()->cmds[data()->curr_cmd][0]))
			data()->curr_cmd = fd_check(data()->curr_cmd);
		else if (mn_is_builtins(data()->cmds[data()->curr_cmd][0]))
			builtins_call(data()->cmds[data()->curr_cmd]);
		else
			execute_cmd();
	}
	free_triple_ptr(data()->cmds);
	swap_fd();
}
