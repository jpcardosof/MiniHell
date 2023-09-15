#include "minishell.h"

void	free_double_ptr(char **str)
{
	int	i;

	i = 0;
	while (str && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_triple_ptr(char ***str)
{
	int	i;
	int	j;

	i = 0;
	while (str && str[i] != NULL)
	{
		j = 0;
		while (str && str[i][j] != NULL)
		{
			free(str[i][j]);
			j++;
		}
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}
