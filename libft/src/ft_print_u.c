/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:52:43 by jferreir          #+#    #+#             */
/*   Updated: 2022/04/05 20:36:18 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_u(unsigned int u, int lenght)
{
	if (u < 10)
		ft_putchar_fd(u + '0', 1);
	else
	{
		lenght = ft_print_u(u / 10, (lenght + 1));
		lenght = ft_print_u(u % 10, (lenght));
	}
	return (lenght);
}
