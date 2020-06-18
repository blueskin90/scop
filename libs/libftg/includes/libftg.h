/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/15 03:54:24 by toliver           #+#    #+#             */
/*   Updated: 2019/01/03 20:32:01 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTG_H
# define LIBFTG_H

# include <math.h>

typedef struct		s_vec
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec;

typedef struct		s_matrix
{
	float			matrix[4][4];
}					t_matrix;

/*
** Generic functions
*/
float				ft_min(float a, float b, float c);
float				ft_max(float a, float b, float c);
/*
** Vector and Vertex matrix and math handling functions
*/

t_vec				vec_x(void);
t_vec				vec_y(void);
t_vec				vec_z(void);
t_vec				vec_init(t_vec a, t_vec b);
t_vec				vec_init0(float x, float y, float z);
t_vec				vec_normalize(t_vec a);
t_vec				vec_norm(t_vec a);
t_vec				vec_add(t_vec a, t_vec b);
t_vec				vec_sub(t_vec a, t_vec b);
t_vec				vec_mul(t_vec a, float s);
t_vec				vec_div(t_vec a, float s);
t_vec				vec_opposite(t_vec a);
t_vec				vec_crossproduct(t_vec a, t_vec b);
float				vec_dotproduct(t_vec a, t_vec b);
float				vec_dot(t_vec a, t_vec b);
float				vec_magnitude(t_vec a);
float				vec_cos(t_vec a, t_vec b);
t_matrix			identity_matrix_init(void);
t_matrix			scale_matrix_init(float scale);
t_matrix			translation_matrix_init(t_vec tranvec);
t_matrix			rotx_matrix_init(float degrees);
t_matrix			roty_matrix_init(float degrees);
t_matrix			rotz_matrix_init(float degrees);
t_matrix			rotmatrix_axis_angle(t_vec axis, float angle);
t_matrix			matrix_mult(t_matrix a, t_matrix b);
t_vec				matrix_mult_vec(t_matrix a, t_vec b);
float				degtorad(float deg);
float				radtodeg(float rad);
float				min_of_vec(t_vec vec);
float				max_of_vec(t_vec vec);
int					vec_is_0(t_vec vec);
#endif
