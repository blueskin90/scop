/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 14:44:47 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 20:01:06 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_hex(unsigned int value, int is_maj)
{
	char			*res;
	int				i;
	char			maj;

	maj = (is_maj) ? 'A' - 10 : 'a' - 10;
	if (!(res = ft_strnew(6)))
		return (NULL);
	ft_bzero(res, 6);
	i = 6;
	while (--i >= 0)
	{
		res[i] = value & 0xf;
		value = (value >> 4);
		res[i] += (res[i] <= 9) ? '0' : maj;
	}
	return (res);
}
