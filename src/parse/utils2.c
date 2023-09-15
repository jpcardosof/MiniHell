/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:26:11 by jferreir          #+#    #+#             */
/*   Updated: 2023/08/05 13:44:22 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_blank(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
		i++;
	return (i);
}

void	skip_non_blank_and_sign_dolar(char **str)
{
	while (**str && **str != ' ' && **str != '\n' && **str != '\t'
		&& **str != '\"' && **str != '$')
		(*str)++;
}

void	handle_env(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t'
		&& str[i] != '\"' && str[i] != '$' && str[i] != '/')
	{
		tmp = strjoin_var(tmp, str[i++]);
		if (ft_strncmp(tmp, "?", 2) == 0)
			break ;
	}
	data()->str_tmp = my_getenv(tmp);
	free(tmp);
	tmp = NULL;
}

void	warn_check(char **str)
{
	data()->warning = 0;
	handle_dollar_sign(*str);
	free(data()->str_tmp);
	data()->str_tmp = NULL;
}

void	characters_special_handle(char **str, int *count)
{
	if ((**str == '|' || **str == '<' || **str == '>'))
	{
		if ((**str == '<' || **str == '>') && (*str)[1] == **str)
			(*str) += 2;
		else
			(*str)++;
	}
	else if (**str == '$')
	{
		warn_check(str);
		(*str)++;
		if (**str == '\0')
			(*count)++;
		while (**str && **str != ' ' && **str != '\n' && **str != '$'
			&& **str != '\t' && **str != '|' && **str != '<' && **str != '>'
			&& **str != '\'' && **str != '\"')
			(*str)++;
		if (data()->warning == -1)
			return ;
	}
	else
		while (**str && **str != ' ' && **str != '\n'
			&& **str != '\t' && **str != '|' && **str != '<' && **str != '>')
			(*str)++;
	(*count)++;
}
