/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_case_insensitive.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvermand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:16:43 by cvermand          #+#    #+#             */
/*   Updated: 2019/01/03 20:01:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp_case_insensitive(const char *s1, const char *s2)
{
	while (s1 && *s1 && ft_tolower(*s1) == ft_tolower(*s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2 && *s1 == '\0')
		return (0);
	return (*((unsigned char*)s1) - *((unsigned char*)s2));
}
