/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:13:02 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:13:26 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

float		vec_magnitude(t_vec a)
{
	return (sqrtf(powf(a.x, 2) + powf(a.y, 2) + powf(a.z, 2)));
}

t_vec		vec_norm(t_vec a)
{
	float	magnitude;
	t_vec	b;

	magnitude = vec_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}

t_vec		vec_normalize(t_vec a)
{
	float	magnitude;
	t_vec	b;

	magnitude = vec_magnitude(a);
	if (magnitude == 0.0)
		return (a);
	b.x = a.x / magnitude;
	b.y = a.y / magnitude;
	b.z = a.z / magnitude;
	b.w = 0;
	return (b);
}
