/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:35:10 by toliver           #+#    #+#             */
/*   Updated: 2020/07/29 23:25:09 by toliver          ###   ########.fr       */
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
#include <math.h>

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define FLAGS ""

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#define MAJOR_V 4
#define MINOR_V 0

enum			e_matrix
{
	IDENTITY,
	TRANSLATION,
	ROTATION,
};

typedef struct	s_vec3int
{
	int			val[3];
}				t_vec3int;

typedef struct	s_vec4int
{
	int			val[4];
}				t_vec4int;

typedef struct	s_vec4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4;

typedef struct	s_mat4
{
	GLfloat		val[4][4];
}				t_mat4;

enum	e_errors
{
	MALLOC,
	NO_VALID_OBJ,
	INVALID_FILE,
	MY_OVERFLOW,
	OPEN,
	TOO_MANY_OBJECTS,
	PARSING_ERROR,
	UNEXPECTED_TOKEN,
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

typedef struct	s_cam
{
	t_vec4		pos;
	t_vec4		front;
	t_vec4		up;
	t_vec4		right;
}				t_cam;

typedef struct	s_mvp
{
	t_mat4		trans;
	GLint		uni_trans;
	t_mat4		rot;
	GLint		uni_rot;
	t_mat4		obj_to_world;
	t_mat4		world_to_view;
	t_mat4		view_projection;
}				t_mvp;

typedef struct	s_obj
{
	char			*name;
	size_t			vertices_nbr;
	size_t			vertices_arr_size;
	t_vec4			*vertices;
	size_t			faces_nbr;
	size_t			faces_arr_size;
	t_face			*faces;
	unsigned int	triangles_nbr;
	unsigned int	*triangle_indices;
	unsigned int	quad_nbr;
	unsigned int	*quad_indices;
}					t_obj;

typedef struct		s_env
{
	char			*name;
	t_obj			obj;
	GLFWwindow		*win;
	GLuint			vbo;	
	GLuint			vao;	
	GLuint			ebo;	
	GLuint			vertex_shader;
	GLuint			fragment_shader;
	GLuint			shader_program;
	t_cam			cam;
	t_mvp			mvp;
	float			delta_time;
}					t_env;

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

/*
** UTILS FUNCTIONS
*/

int		ft_parsing_error(char *line, int *mode);
int		ft_error(int error, char *str);
t_env	*ft_getenv(void);
void	ft_setenv(t_env *env);
int		ft_error(int error, char *str);
void	ft_usage(void);

/*
** CALLBACK FUNCTIONS
*/

void	error_callback(int error, const char* description);
void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/*
** INIT FUNCTIONS
*/

int		ft_init(t_env *env);

/*
** VECTOR FUNCTIONS
*/

t_vec4	vec_set(float x, float y, float z);
t_vec4	vec_add(t_vec4 a, t_vec4 b);
t_vec4	vec_sub(t_vec4 a, t_vec4 b);
t_vec4	vec_opp(t_vec4 a);
t_vec4	vec_mul(t_vec4 a, float val);
t_vec4	vec_normalize(t_vec4 a);

/*
** MATRIX FUNCTIONS
*/

void	ft_matrix_set_identity(t_mat4 *ptr);
void	ft_matrix_set_tran(t_mat4 *ptr, t_vec4 tran);
void	ft_matrix_set_rot(t_mat4 *mat, t_vec4 axis, float angle);

/*
** INPUT FUNCTIONS
*/

void	ft_move_camera(t_env *env);

#endif
