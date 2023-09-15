/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:36:35 by jferreir          #+#    #+#             */
/*   Updated: 2023/08/03 11:45:46 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_tokens(int nbr_tokens)
{
	char	**tokens;

	tokens = (char **)ft_calloc((nbr_tokens + 1), sizeof(char *));
	tokens[nbr_tokens] = NULL;
	if (!tokens)
	{
		perror("Error while malloc tokens.");
		return (NULL);
	}
	return (tokens);
}

int	token_inside_quote(char	*str, char **token)
{
	int		size;

	if (str[1] != *str)
	{
		size = quotes_inside(str, *str);
		if (((str[1] == '>' || str[1] == '<' || str[1] == '|'))
			&& (str[2] == *str || str[3] == *str) && (str[2] != '|'))
			(*token) = handle_single_spc_quote(str);
		else if (data()->warning == -1)
		{
			(*token) = strjoin_null((*token), env_var(str++));
		}
		else
			(*token) = strjoin_null((*token),
					ft_substr(++str, 0, size));
		return (size + 2);
	}
	else
		return (2);
}

int	token_special_char(char *str, char **token, int *i)
{
	if (str[1] == *str && (*str == '>' || *str == '<'))
	{
		(*token) = strjoin_null((*token), ft_substr(str, 0, 2));
		if (str[2] != ' ')
			(*i)++;
		return (2);
	}
	else
	{
		(*token) = ft_substr(str, 0, 1);
		if (str[1] != ' ')
			(*i)++;
		return (1);
	}
}

int	token_space_dolar_sig(char *str, char **token, int nbr_tokens)
{
	int	size;

	size = handle_dollar_sign(str);
	if (data()->warning != -1)
	{
		if (data()->str_tmp != NULL)
			(*token) = strjoin_null((*token), ft_substr(data
						()->str_tmp, 0, ft_strlen(data()->str_tmp)));
		free(data()->str_tmp);
		data()->str_tmp = NULL;
	}
	else if (nbr_tokens > 0)
		return (0);
	else
		if (str[size + 1] == ' ')
			size = (size + 1) + skip_blank(str);
	return (size + 1);
}

int	token_other_chars(char *str, char **token, int *i)
{
	int	size;

	size = quotes_outside(str);
	(*token) = strjoin_null((*token), ft_substr(str, 0, (size + 1)));
	if (str[size + 1] == '|' || str[size + 1] == '>' || str[size + 1] == '<' )
		(*i)++;
	return (size + 1);
}
