/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 15:56:38 by jferreir          #+#    #+#             */
/*   Updated: 2023/08/02 17:29:01 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_input(int tmp_curr)
{
	if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
		return ;
	if (data()->fd[0][0] != STDIN_FILENO)
		close(data()->fd[0][0]);
	if (!(access(data()->cmds[tmp_curr][1], R_OK) == 0))
	{
		if (errno == EACCES && data()->error == 0)
		{
			msg_error(NULL, data()->cmds[tmp_curr][1], \
			": Permission denied", 1);
			data()->fd[0][0] = -1;
			return ;
		}
	}
	(data()->fd[0][0]) = open(data()->cmds[tmp_curr][1], O_RDONLY);
	if (data()->fd[0][0] < 0 && data()->error == 0)
		msg_error(NULL, data()->cmds[tmp_curr][1], \
		": No such file or directory", 1);
}

void	fd_red_append(int tmp_curr)
{
	if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
		return ;
	if (data()->fd[0][0] != STDIN_FILENO)
		close(data()->fd[0][0]);
	if (!(access(data()->cmds[tmp_curr][1], W_OK) == 0))
	{
		if (errno == EACCES && data()->error == 0)
		{
			msg_error(NULL, data()->cmds[tmp_curr][1], \
			": Permission denied", 1);
			data()->fd[0][1] = -1;
			return ;
		}
	}
	(data()->fd[0][1]) = open(data()->cmds[tmp_curr][1], \
	O_RDWR | O_CREAT | O_APPEND, 0664);
	if (data()->fd[0][1] < 0 && data()->error == 0)
		msg_error("Error to create/read the redirected file named: ", \
		data()->cmds[tmp_curr][1], NULL, 1);
}

void	fd_redirect(int tmp_curr)
{
	if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
		return ;
	if (data()->fd[0][1] != STDOUT_FILENO)
		close(data()->fd[0][1]);
	if (!(access(data()->cmds[tmp_curr][1], W_OK) == 0))
	{
		if (errno == EACCES && data()->error == 0)
		{
			msg_error(NULL, data()->cmds[tmp_curr][1], \
			": Permission denied", 1);
			data()->fd[0][1] = -1;
			return ;
		}
	}
	(data()->fd[0][1]) = open(data()->cmds[tmp_curr][1], \
	O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (data()->fd[0][1] < 0 && data()->error == 0)
		msg_error("Error to create/read the redirected file named: ", \
		data()->cmds[tmp_curr][1], NULL, 1);
}

void	fd_pipe(void)
{
	int	new_fd[2];

	pipe(new_fd);
	if (data()->fd[1][0] == STDIN_FILENO)
		data()->fd[1][0] = new_fd[0];
	else
		close(new_fd[0]);
	if (data()->fd[0][1] == STDOUT_FILENO)
		data()->fd[0][1] = new_fd[1];
	else
		close(new_fd[1]);
}

int	fd_check(int tmp_curr)
{
	if (mn_strcmp(data()->cmds[tmp_curr][0], "|"))
		fd_pipe();
	else if (mn_strcmp(data()->cmds[tmp_curr][0], ">"))
		fd_redirect(tmp_curr);
	else if (mn_strcmp(data()->cmds[tmp_curr][0], ">>"))
		fd_red_append(tmp_curr);
	else if (mn_strcmp(data()->cmds[tmp_curr][0], "<"))
		fd_input(tmp_curr);
	else if (mn_strcmp(data()->cmds[tmp_curr][0], "<<"))
		fd_heredoc(tmp_curr);
	if (data()->cmds[tmp_curr + 1] != NULL \
	&& is_spc(data()->cmds[tmp_curr + 1][0]) \
	&& is_spc(data()->cmds[tmp_curr][0]) != 1)
	{
		tmp_curr = fd_check(tmp_curr + 1);
		tmp_curr--;
	}
	return (tmp_curr + 1);
}
