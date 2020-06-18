/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:08:15 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:08:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_matrix		matrix_mult(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int			x;
	int			y;

	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			c.matrix[y][x] = a.matrix[y][0] * b.matrix[0][x]
				+ a.matrix[y][1] * b.matrix[1][x]
				+ a.matrix[y][2] * b.matrix[2][x]
				+ a.matrix[y][3] * b.matrix[3][x];
			x++;
		}
		y++;
	}
	return (c);
}

t_vec			matrix_mult_vec(t_matrix a, t_vec b)
{
	t_vec		c;

	c.x = a.matrix[0][0] * b.x + a.matrix[0][1] * b.y + a.matrix[0][2] * b.z
		+ a.matrix[0][3] * b.w;
	c.y = a.matrix[1][0] * b.x + a.matrix[1][1] * b.y + a.matrix[1][2] * b.z
		+ a.matrix[1][3] * b.w;
	c.z = a.matrix[2][0] * b.x + a.matrix[2][1] * b.y + a.matrix[2][2] * b.z
		+ a.matrix[2][3] * b.w;
	c.w = a.matrix[3][0] * b.x + a.matrix[3][1] * b.y + a.matrix[3][2] * b.z
		+ a.matrix[3][3] * b.w;
	return (c);
}
