/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:43:43 by jferreir          #+#    #+#             */
/*   Updated: 2023/08/01 17:04:52 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_err(void)
{
	if (data()->fd[0][0] != 0 || data()->fd[0][1] != 1)
	{
		data()->error = 2;
		return (1);
	}
	return (0);
}

long long int	ft_atoli_checker(char *nptr, int i, int sing)
{
	long long int	result;
	int				size;

	size = 0;
	result = 0;
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = (result * 10) + (nptr[i] - '0');
		size++;
		if (size == 19)
		{
			if (sing == -1 && nptr[i] > '7')
				return (0);
			else if (nptr[i] > '7')
				return (0);
		}
		else if (size > 19)
			return (0);
		i++;
	}
	return (result * sing);
}

long long int	ft_atoli(char *nptr)
{
	int	i;
	int	sing;

	i = 0;
	sing = 1;
	while (nptr[i] && (nptr[i] == '\f' || nptr[i] == ' ' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v'))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sing = -1;
		i++;
	}
	if (sing == -1 && !ft_strncmp("9223372036854775808", &nptr[i], 19))
		return (-922337203685477580 * 10 - 8);
	return (ft_atoli_checker(nptr, i, sing));
}

void	ft_exit(char **str)
{
	long long int	i;

	i = 0;
	if (ft_exit_err())
		return ;
	printf("exit\n");
	if (str[1] != NULL && str[2] != NULL)
	{
		i = 1;
		msg_error(NULL, NULL, "exit: too many arguments", 1);
	}
	else if (str[1] != NULL)
	{
		i = ft_atoli(str[1]);
		if ((!ft_isdigit(str[1][0]) && str[1][0] != '-' && str[1][0] != '+') \
		|| (i == 0 && (!mn_strcmp(str[1], "0") || !mn_strcmp(str[1], "+0"))))
		{
			i = 2;
			msg_error("exit: ", str[1], ": numeric argument required", i);
		}
	}
	free(data()->str_cmd);
	free_double_ptr(data()->env_p);
	free_triple_ptr(data()->cmds);
	exit(i);
}
