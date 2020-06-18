/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 08:41:12 by toliver           #+#    #+#             */
/*   Updated: 2018/01/28 16:28:23 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_ftoa(float n, unsigned int decitoprint)
{
	char			*integer;
	char			*decimal;
	char			*final;
	unsigned int	i;

	decitoprint = (decitoprint > 10) ? 10 : decitoprint;
	if ((n < 0 && n > -1 && (int)n == 0 && !(integer = ft_strdup("-0"))) ||
			((n >= 0 || n <= -1) && !(integer = ft_itoa((int)n))))
		return (NULL);
	if ((i = 0) == 0 && decitoprint <= 0)
		return (integer);
	n = (n < 0) ? -(n - (int)n) : n - (int)n;
	if (!(decimal = malloc(sizeof(char) * decitoprint + 2)))
		return (NULL);
	decimal[0] = '.';
	while (++i <= decitoprint && (n = n * 10) >= 0)
	{
		decimal[i] = (int)n + '0';
		n -= (int)n;
	}
	decimal[i] = '\0';
	final = ft_strjoin(integer, decimal);
	free(decimal);
	free(integer);
	return (final);
}
