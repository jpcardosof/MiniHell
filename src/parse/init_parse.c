#include "minishell.h"

// Main function of the parse unit
void	init_parse(void)
{
	error_var();
	if (get_tokens() == 0)
	{
		ft_unset(data()->env_p, "?");
		return ;
	}
	add_history(data()->str_cmd);
	if (data()->tokens)
		cmd_to_exec();
}

char	*my_getenv(char *str)
{
	int		size;
	int		i;
	int		j;
	char	*tmp;

	if (str == NULL || *str == '\0')
		return (NULL);
	size = ft_strlen(str);
	j = 0;
	while (data()->env_p[j])
	{
		tmp = data()->env_p[j];
		i = 0;
		while (tmp[i] != '=' && tmp[i] != '\0')
			i++;
		if (tmp[i] == '=' && i == size && ft_strncmp(str, tmp, i) == 0)
			return (ft_strdup(&tmp[i + 1]));
		j++;
	}
	return (NULL);
}
