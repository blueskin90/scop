/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:18:38 by toliver           #+#    #+#             */
/*   Updated: 2020/07/29 18:39:16 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec4	vec_opp(t_vec4 a)
{
	return ((t_vec4){-a.x, -a.y, -a.z, 1});
}

t_vec4	vec_add(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a.x + b.x, a.y + b.y, a.z + b.z, 1});
}

t_vec4	vec_sub(t_vec4 a, t_vec4 b)
{
	return ((t_vec4){a.x - b.x, a.y - b.y, a.z - b.z, 1});
}

float	vec_norm(t_vec4 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));	
}

t_vec4	vec_normalize(t_vec4 a)
{
	float	norm;
	
	norm = vec_norm(a);
	return ((t_vec4){a.x / norm, a.y / norm, a.z / norm, 1});
}

t_vec4	vec_mul(t_vec4 a, float val)
{
	return ((t_vec4){a.x * val, a.y * val, a.z * val, 1});
}

t_vec4	vec_set(float x, float y, float z)
{
	return ((t_vec4){x, y, z, 1});
}
