/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:35:10 by toliver           #+#    #+#             */
/*   Updated: 2020/06/18 11:36:05 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION
#include "libft.h"
#include "libftg.h"
#include "libftprintf.h"
#include  <fcntl.h>

#define FLAGS ""

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct		s_face
{
	size_t			indice_nbr;
	t_vec4			*indices;// 1 vec par indice
}					t_face;

typedef struct		s_group
{
	char			*name;
	size_t			faces_nbr;
	t_face			*faces;
}					t_group;

typedef struct		s_veclist
{
	t_vec4			vec;
	struct	s_list	*next;
}					t_veclist;

typedef struct	s_grp
{
	int			type;
	void		*ptr;
}				t_grp;



typedef struct	s_obj
{
	char		*name;
	size_t		v_nbr;
	t_vec4		*v;
	size_t		vt_nbr;
	t_vec4		*vt;
	size_t		vn_nbr;
	t_vec4		*vn;
	size_t		faces_nbr;
	t_face		*faces;
}				t_obj;

const char* const g_error_value[] =
{
	"malloc failed",
	"no valid .obj file given",
	"invalid file was given:  ",
	"couldn't open file: ",
	0
}; 

enum	e_errors
{
	MALLOC,
	NO_VALID_OBJ,
	INVALID_FILE,
	OPEN,
};

typedef struct	s_env
{
	char		*name;
}				t_env;
#endif
