/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init_rot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:07:45 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:36:27 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_matrix		rotx_matrix_init(float degrees)
{
	t_matrix	rotationmatrix;
	float		rad;
	float		cos;
	float		sin;

	rad = degtorad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmatrix = identity_matrix_init();
	rotationmatrix.matrix[1][1] = cos;
	rotationmatrix.matrix[1][2] = -sin;
	rotationmatrix.matrix[2][1] = sin;
	rotationmatrix.matrix[2][2] = cos;
	return (rotationmatrix);
}

t_matrix		roty_matrix_init(float degrees)
{
	t_matrix	rotationmatrix;
	float		rad;
	float		cos;
	float		sin;

	rad = degtorad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmatrix = identity_matrix_init();
	rotationmatrix.matrix[0][0] = cos;
	rotationmatrix.matrix[0][2] = sin;
	rotationmatrix.matrix[2][0] = -sin;
	rotationmatrix.matrix[2][2] = cos;
	return (rotationmatrix);
}

t_matrix		rotz_matrix_init(float degrees)
{
	t_matrix	rotationmatrix;
	float		rad;
	float		cos;
	float		sin;

	rad = degtorad(degrees);
	cos = cosf(rad);
	sin = sinf(rad);
	rotationmatrix = identity_matrix_init();
	rotationmatrix.matrix[0][0] = cos;
	rotationmatrix.matrix[0][1] = -sin;
	rotationmatrix.matrix[1][0] = sin;
	rotationmatrix.matrix[1][1] = cos;
	return (rotationmatrix);
}

t_matrix		matrix_axis_angle_get(t_vec axis, float cos, float sin, float t)
{
	t_matrix	matrix;
	float		tmp1;
	float		tmp2;

	matrix = identity_matrix_init();
	matrix.matrix[0][0] = cos + axis.x * axis.x * t;
	matrix.matrix[1][1] = cos + axis.y * axis.y * t;
	matrix.matrix[2][2] = cos + axis.z * axis.z * t;
	tmp1 = axis.x * axis.y * t;
	tmp2 = axis.z * sin;
	matrix.matrix[1][0] = tmp1 + tmp2;
	matrix.matrix[0][1] = tmp1 - tmp2;
	tmp1 = axis.x * axis.z * t;
	tmp2 = axis.y * sin;
	matrix.matrix[2][0] = tmp1 - tmp2;
	matrix.matrix[0][2] = tmp1 + tmp2;
	tmp1 = axis.y * axis.z * t;
	tmp2 = axis.x * sin;
	matrix.matrix[2][1] = tmp1 + tmp2;
	matrix.matrix[1][2] = tmp1 - tmp2;
	return (matrix);
}

t_matrix		rotmatrix_axis_angle(t_vec axis, float angle)
{
	float		cos;
	float		sin;
	float		t;
	t_matrix	matrix;

	if (angle == 0 || angle == NAN || vec_magnitude(axis) == 0)
		return (identity_matrix_init());
	cos = cosf(angle);
	sin = sinf(angle);
	t = 1.0 - cos;
	matrix = matrix_axis_angle_get(axis, cos, sin, t);
	return (matrix);
}
