/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:16:49 by toliver           #+#    #+#             */
/*   Updated: 2018/11/05 17:57:18 by cvermand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		ft_max(float a, float b, float c)
{
	if (a >= b && a >= c)
		return (a);
	if (b >= a && b >= c)
		return (b);
	return (c);
}

float		ft_min(float a, float b, float c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}
