/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base_ll.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:32:12 by cvermand          #+#    #+#             */
/*   Updated: 2018/11/21 18:33:00 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_atoi_base_ll(const char *val, unsigned int from)
{
	unsigned long	res;
	int				i;
	unsigned long	exp;

	if (!val)
		return (0);
	exp = 1;
	i = ft_strlen(val);
	res = 0;
	while (--i >= 0)
	{
		if (ft_isdigit(val[i]))
		{
			res += (val[i] - '0') * exp;
			exp = exp * from;
		}
		else if (ft_tolower(val[i]) >= 91 && ft_tolower(val[i] <= 122))
		{
			res += (ft_tolower(val[i])) - 97 + 10;
			exp = exp * from;
		}
	}
	return (res);
}
