#include "minishell.h"

int	mn_is_builtins(char *cmd)
{
	if (mn_strcmp(cmd, "echo"))
		return (1);
	else if (mn_strcmp(cmd, "cd"))
		return (1);
	else if (mn_strcmp(cmd, "pwd"))
		return (1);
	else if (mn_strcmp(cmd, "export"))
		return (1);
	else if (mn_strcmp(cmd, "unset"))
		return (1);
	else if (mn_strcmp(cmd, "env"))
		return (1);
	else if (mn_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	builtins_call(char **cmd)
{
	int	tmp_curr;

	tmp_curr = data()->curr_cmd + 1;
	if (data()->cmds[tmp_curr] != NULL && is_spc(data()->cmds[tmp_curr][0]))
		tmp_curr = fd_check(tmp_curr);
	if (mn_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (mn_strcmp(cmd[0], "cd"))
		ft_cd(cmd);
	else if (mn_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (mn_strcmp(cmd[0], "export"))
		ft_export();
	else if (mn_strcmp(cmd[0], "unset"))
		ft_unset(data()->env_p, data()->cmds[data()->curr_cmd][1]);
	else if (mn_strcmp(cmd[0], "env"))
		ft_env(data()->env_p);
	else if (mn_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	data()->curr_cmd = tmp_curr;
	swap_fd();
}

void	child_exit(void)
{
	free_all();
	swap_fd();
	swap_fd();
	exit(0);
}
