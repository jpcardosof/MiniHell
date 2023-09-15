/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 22:21:12 by jferreir          #+#    #+#             */
/*   Updated: 2023/07/31 13:38:24 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mn_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1 && s2 && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1 && s2 && s1[i] != s2[i])
		return (0);
	return (1);
}

int	is_spc(char *cmd)
{
	if (mn_strcmp(cmd, "|"))
		return (1);
	else if (mn_strcmp(cmd, ">"))
		return (2);
	else if (mn_strcmp(cmd, ">>"))
		return (3);
	else if (mn_strcmp(cmd, "<"))
		return (4);
	else if (mn_strcmp(cmd, "<<"))
		return (5);
	return (0);
}
