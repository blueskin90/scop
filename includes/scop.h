/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:35:10 by toliver           #+#    #+#             */
/*   Updated: 2020/07/28 00:34:07 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# define GL_SILENCE_DEPRECATION
#define __gl_h_
# define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#include "libft.h"
#include "libftprintf.h"
#include  <fcntl.h>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h> // GLFW helper library
#include <sys/errno.h>

#define FLAGS ""

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#define MAJOR_V 4
#define MINOR_V 0

typedef struct	s_vec3int
{
	int			x;
	int			y;
	int			z;
}				t_vec3int;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct				s_vec3intlist
{
	t_vec3int				vec;
	struct s_vec3intlist	*next;
}							t_vec3intlist;

typedef struct			s_vec4list
{
	t_vec4				vec;
	struct	s_vec4list	*next;
}						t_vec4list;

enum	e_errors
{
	MALLOC,
	NO_VALID_OBJ,
	INVALID_FILE,
	OPEN,
	TOO_MANY_OBJECTS,
	PARSING_ERROR,
	MAXVALUE,
};

typedef struct	s_obj
{
	char		*name;
	size_t		vertices_nbr;
	t_vec4		*vertices;
	size_t		faces_nbr;
	t_vec3int	*faces;
}				t_obj;

typedef struct	s_env
{
	char		*name;
	t_obj		obj;
	GLFWwindow	*win;
}				t_env;

enum	e_parse_mode
{
	INIT,
	VERT,
	FACE,
	ERR,
};

/*
** GLOBAL
*/

extern const char * const g_error_value[MAXVALUE + 1];



int		obj_parse(t_env *env, char *file);
int		ft_error(int error, char *str);
t_env	*ft_getenv(void);
int		ft_error(int error, char *str);

#endif
