/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 06:15:34 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:15:43 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec_cos(t_vec a, t_vec b)
{
	return (vec_dotproduct(a, b) / (vec_magnitude(a)
				* vec_magnitude(b)));
}

float		vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float		vec_dotproduct(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec		vec_div(t_vec a, float s)
{
	t_vec	b;

	if (s == 0.0)
		return (a);
	b.x = a.x / s;
	b.y = a.y / s;
	b.z = a.z / s;
	b.w = 0;
	return (b);
}

t_vec		vec_crossproduct(t_vec a, t_vec b)
{
	t_vec c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	c.w = 0;
	return (c);
}
