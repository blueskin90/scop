/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 20:06:45 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:08:37 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftg.h"

t_matrix		identity_matrix_init(void)
{
	t_matrix	id;

	id.matrix[0][0] = 1.0;
	id.matrix[0][1] = 0.0;
	id.matrix[0][2] = 0.0;
	id.matrix[0][3] = 0.0;
	id.matrix[1][0] = 0.0;
	id.matrix[1][1] = 1.0;
	id.matrix[1][2] = 0.0;
	id.matrix[1][3] = 0.0;
	id.matrix[2][0] = 0.0;
	id.matrix[2][1] = 0.0;
	id.matrix[2][2] = 1.0;
	id.matrix[2][3] = 0.0;
	id.matrix[3][0] = 0.0;
	id.matrix[3][1] = 0.0;
	id.matrix[3][2] = 0.0;
	id.matrix[3][3] = 1.0;
	return (id);
}

t_matrix		scale_matrix_init(float scale)
{
	t_matrix	scalematrix;

	scalematrix = identity_matrix_init();
	scalematrix.matrix[0][0] *= scale;
	scalematrix.matrix[1][1] *= scale;
	scalematrix.matrix[2][2] *= scale;
	return (scalematrix);
}

t_matrix		translation_matrix_init(t_vec tranvec)
{
	t_matrix	translationmatrix;

	translationmatrix = identity_matrix_init();
	translationmatrix.matrix[0][3] = tranvec.x;
	translationmatrix.matrix[1][3] = tranvec.y;
	translationmatrix.matrix[2][3] = tranvec.z;
	return (translationmatrix);
}
