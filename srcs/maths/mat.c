/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 13:56:25 by toliver           #+#    #+#             */
/*   Updated: 2020/08/23 13:57:30 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"


void	ft_matrix_set_identity(t_mat4 *ptr)
{
	ft_bzero(ptr, sizeof(t_mat4));
	ptr->val[0][0] = 1;
	ptr->val[1][1] = 1;
	ptr->val[2][2] = 1;
	ptr->val[3][3] = 1;
}

void	ft_matrix_set_tran(t_mat4 *ptr, t_vec4 tran)
{
	ft_bzero(ptr, sizeof(t_mat4));
	ptr->val[0][0] = 1;
	ptr->val[1][1] = 1;
	ptr->val[2][2] = 1;
	ptr->val[3][3] = 1;
	ptr->val[3][0] = tran.x;
	ptr->val[3][1] = tran.y;
	ptr->val[3][2] = tran.z;
}

void	ft_matrix_set_rot(t_mat4 *mat, t_vec4 axis, float angle)
{
	float	sin;
	float	cos;

	angle = degtorad(angle);
	sin = sinf(angle);
	cos = cosf(angle);
	ft_matrix_set_identity(mat);
	mat->val[0][0] = cos + axis.x * axis.x * (1.0 - cos);
	mat->val[0][1] = axis.x * axis.y * (1.0 - cos) + axis.z * sin;
	mat->val[0][2] = axis.x * axis.z * (1.0 - cos) - axis.y * sin;
	mat->val[1][0] = axis.x * axis.y * (1.0 - cos) - axis.z * sin;
	mat->val[1][1] = cos + axis.y * axis.y * (1.0 - cos);
	mat->val[1][2] = axis.y * axis.z * (1.0 - cos) + axis.x * sin;
	mat->val[2][0] = axis.x * axis.z * (1.0 - cos) + axis.y * sin;
	mat->val[2][1] = axis.y * axis.z * (1.0 - cos) - axis.x * sin;
	mat->val[2][2] = cos + axis.z * axis.z * (1.0 - cos);
}

void	ft_matrix_set_scale(t_mat4 *ptr, float scale)
{
	ft_bzero(ptr, sizeof(t_mat4));
	ptr->val[0][0] = scale;
	ptr->val[1][1] = scale;
	ptr->val[2][2] = scale;
	ptr->val[3][3] = 1;
}

void	ft_matrix_dump(t_mat4 *ptr)
{
	ft_printf("[%.2f][%.2f][%.2f][%.2f]\n", ptr->val[0][0], ptr->val[0][1], ptr->val[0][2], ptr->val[0][3]);
	ft_printf("[%.2f][%.2f][%.2f][%.2f]\n", ptr->val[1][0], ptr->val[1][1], ptr->val[1][2], ptr->val[1][3]);
	ft_printf("[%.2f][%.2f][%.2f][%.2f]\n", ptr->val[2][0], ptr->val[2][1], ptr->val[2][2], ptr->val[2][3]);
	ft_printf("[%.2f][%.2f][%.2f][%.2f]\n", ptr->val[3][0], ptr->val[3][1], ptr->val[3][2], ptr->val[3][3]);
}

t_vec4	ft_matrix_mult_vec(t_mat4 *mat, t_vec4 vec)
{
	float	x;
	float	y;
	float	z;

	x = vec.x * mat->val[0][0] + vec.y * mat->val[1][0] + vec.z * mat->val[2][0] + mat->val[3][0];
	y = vec.x * mat->val[0][1] + vec.y * mat->val[1][1] + vec.z * mat->val[2][1] + mat->val[3][1];
	z = vec.x * mat->val[0][2] + vec.y * mat->val[1][2] + vec.z * mat->val[2][2] + mat->val[3][2];
	return ((t_vec4){x, y, z, 1});
}

t_mat4	ft_matrix_mult_matrix(t_mat4 *a, t_mat4 *b)
{
	t_mat4		c;
	int			x;
	int			y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			c.val[y][x] = a->val[y][0] * b->val[0][x]
				+ a->val[y][1] * b->val[1][x]
				+ a->val[y][2] * b->val[2][x]
				+ a->val[y][3] * b->val[3][x];
			x++;
		}
		y++;
	}
	return (c);
}
