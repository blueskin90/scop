/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:10:33 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 20:00:45 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char				*move_to_start_of_number(char *str, int *sign)
{
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			*sign = -1;
		str++;
	}
	return (str);
}

static char				*before_dec(char *str, float *result)
{
	*result = 0;
	while (ft_isdigit(*str))
	{
		*result = *result * 10 + (*str - 48);
		str++;
	}
	return (str);
}

static	float			get_exp(int i)
{
	float	exp;

	exp = 1;
	while (i--)
		exp *= 10;
	return (exp);
}

float					ft_atof(char *str)
{
	float				result;
	int					sign;
	int					i;

	i = 1;
	result = 0;
	sign = 1;
	str = move_to_start_of_number(str, &sign);
	str = before_dec(str, &result);
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result = result + ((*str - 48) / get_exp(i));
			str++;
			i++;
		}
	}
	return (result * (float)sign);
}
