/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_lenght_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 03:10:51 by jferreir          #+#    #+#             */
/*   Updated: 2022/05/09 01:42:00 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_check_lenght_int(int d)
{
	int		lenght;
	char	*str;

	str = ft_itoa(d);
	lenght = ft_strlen(str);
	free(str);
	return (lenght);
}
