/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 04:25:54 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:15:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_vec		vec_add(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = 0;
	return (c);
}

t_vec		vec_sub(t_vec a, t_vec b)
{
	t_vec	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = 0;
	return (c);
}

t_vec		vec_mul(t_vec a, float s)
{
	t_vec	b;

	b.x = a.x * s;
	b.y = a.y * s;
	b.z = a.z * s;
	b.w = 0;
	return (b);
}

t_vec		vec_opposite(t_vec a)
{
	t_vec	b;

	b.x = -a.x;
	b.y = -a.y;
	b.z = -a.z;
	b.w = 0;
	return (b);
}
