#include "minishell.h"

void	msg_error(char *option, char *var_option, char *msg, int err)
{
	errno = err;
	data()->error = err;
	ft_putstr_fd("Minishell: ", 2);
	if (option != NULL)
		ft_putstr_fd(option, 2);
	if (var_option != NULL)
		ft_putstr_fd(var_option, 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

void	permission_checker(void)
{
	if (!(access(data()->cmds[data()->curr_cmd][0], R_OK) == 0) \
	&& errno == EACCES)
	{
		msg_error(NULL, data()->cmds[data()->curr_cmd][0], \
		": Permission denied", 1);
		free_all();
		exit(126);
	}
	else
		msg_error(NULL, data()->cmds[data()->curr_cmd][0], \
		": No such file or directory", 127);
	free_all();
	exit(127);
}

void	exec_error(void)
{
	int		i;

	i = 0;
	while (data()->cmds[data()->curr_cmd][0][i] != '\0')
	{
		if (data()->cmds[data()->curr_cmd][0][i] == '/')
		{
			if (chdir(data()->cmds[data()->curr_cmd][0]) < 0)
				permission_checker();
			else
			{
				msg_error(NULL, data()->cmds[data()->curr_cmd][0], \
				": Is a directory", 126);
				free_all();
				exit(126);
			}
		}
		i++;
	}
	msg_error(NULL, data()->cmds[data()->curr_cmd][0], \
	": command not found", 127);
	free_all();
	exit(127);
}

void	free_all(void)
{
	free(data()->str_cmd);
	free_double_ptr(data()->env_p);
	free_triple_ptr(data()->cmds);
}

void	exit_child(void)
{
	free_all();
	swap_fd();
	swap_fd();
	exit(1);
}
