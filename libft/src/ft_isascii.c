/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jferreir <jferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 01:22:44 by jferreir          #+#    #+#             */
/*   Updated: 2021/12/07 01:18:24 by jferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// isascii() checks whether c is a 7-bit unsigned char value that
// fits into the ASCII character set.

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
	{
		return (1);
	}
	else
		return (0);
}
