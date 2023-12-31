/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:00:44 by jferreir          #+#    #+#             */
/*   Updated: 2022/04/07 20:50:37 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_p(unsigned long d)
{
	int		lenght;

	write(1, "0x", 2);
	lenght = ft_decimal_to_hexadecimal(d, 0, 'p');
	lenght += 2;
	return (lenght);
}
