/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:43:08 by jferreir          #+#    #+#             */
/*   Updated: 2023/08/02 17:18:24 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **str)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		if (data()->fd[0][0] < 0 || data()->fd[0][1] < 0)
			exit_child();
		dup2(data()->fd[0][1], STDOUT_FILENO);
		while (str && str[i] != NULL)
			printf("%s\n", str[i++]);
		swap_fd();
		swap_fd();
		free_all();
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		data()->error = 0;
		if (status > 0)
			data()->error = status / 256;
	}
}

void	ft_env_exec(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
		printf("%s\n", str[i++]);
}
