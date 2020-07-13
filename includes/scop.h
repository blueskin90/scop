/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:35:10 by toliver           #+#    #+#             */
/*   Updated: 2020/07/13 01:19:38 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION

#include "libft.h"
#include "libftprintf.h"
#include  <fcntl.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <sys/errno.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define FLAGS ""

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

enum	e_errors
{
	MALLOC,
	NO_VALID_OBJ,
	INVALID_FILE,
	OPEN,
	TOO_MANY_OBJECTS,
	PARSING_ERROR,
	UNEXPECTED_TOKEN,
	OVERFLOW,
	NOT_ENOUGH_INDICES,
	WRONG_FACE_VALUE,
	NO_FACES,
	MAXVALUE,
};

typedef struct	s_face
{
	size_t		size;
	int			*arr;
}				t_face;

typedef struct	s_obj
{
	char		*name;
	size_t		vertices_nbr;
	size_t		vertices_arr_size;
	t_vec4		*vertices;
	size_t		faces_nbr;
	size_t		faces_arr_size;
	t_face		*faces;
}				t_obj;

typedef struct	s_env
{
	char		*name;
	t_obj		obj;
}				t_env;

enum	e_parse_mode
{
	INIT,
	VERT,
	FACE,
	ERR,
	END,
};

/*
** GLOBAL
*/

extern const char * const g_error_value[MAXVALUE + 1];



int		obj_parse(t_env *env, char *file);
int		ft_parsing_error(char *line, int *mode);
int		ft_error(int error, char *str);
t_env	*ft_getenv(void);
int		ft_error(int error, char *str);

#endif
