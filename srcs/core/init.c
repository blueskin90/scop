/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:30:39 by toliver           #+#    #+#             */
/*   Updated: 2020/07/31 07:10:56 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		ft_init_window(t_env *env)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MAJOR_V);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MINOR_V);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, env->obj.name, NULL, NULL);
	if (!window)
	{
		ft_dprintf(2, "Couldn't create window !\n");
		return (0);
	}
	env->win = window;
	glfwMakeContextCurrent(window);
	return (1);
}

int		ft_init_glfw(void)
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return (0);
	} 
	glfwSetErrorCallback(error_callback);
	return (1);
}

void	ft_display_infos(void)
{
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
}

int		ft_create_buffers(t_env *env)
{
	glGenVertexArrays(1, &(env->vao));
	glGenBuffers(1, &(env->vbo));
	glGenBuffers(1, &(env->ebo));

	glBindVertexArray(env->vao);

	glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * env->obj.vertices_nbr, env->obj.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * env->obj.triangles_nbr, env->obj.triangle_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return (1);
}

int		ft_init_vertex_shader(t_env *env)
{
	int  		success;
	char		buf[513];
	const char	*vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec4 aPos;\n"
	"uniform mat4 trans;\n"
	"uniform mat4 rot;\n"
	"uniform mat4 scale;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = scale * trans * rot * vec4(aPos.x, aPos.y, aPos.z, aPos.w);\n"
    "}\0";

	env->vertex_shader = glCreateShader(GL_VERTEX_SHADER);	
	glShaderSource(env->vertex_shader, 1, &vertexShaderSource, NULL);
	glCompileShader(env->vertex_shader);
	glGetShaderiv(env->vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		ft_bzero(buf, 513);
		glGetShaderInfoLog(env->vertex_shader, 512, NULL, buf);
		ft_dprintf(2, "Couldn't Compile Vertex Shader: %s\n", buf);
		return (0);
	}
	return (1);
}

int		ft_init_fragment_shader(t_env *env)
{
	int  		success;
	char		buf[513];
	const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

	env->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);	
	glShaderSource(env->fragment_shader, 1, &fragmentShaderSource, NULL);
	glCompileShader(env->fragment_shader);
	glGetShaderiv(env->fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		ft_bzero(buf, 513);
		glGetShaderInfoLog(env->fragment_shader, 512, NULL, buf);
		ft_dprintf(2, "Couldn't Compile Fragment Shader: %s\n", buf);
		return (0);
	}
	return (1);
}

int		ft_init_shader_program(t_env *env)
{
	int  		success;
	char		buf[513];

	env->shader_program = glCreateProgram();
	glAttachShader(env->shader_program, env->vertex_shader);
	glAttachShader(env->shader_program, env->fragment_shader);
	glLinkProgram(env->shader_program);
	glGetProgramiv(env->shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		ft_bzero(buf, 513);
		glGetShaderInfoLog(env->shader_program, 512, NULL, buf);
		ft_dprintf(2, "Couldn't Link Shader Program: %s\n", buf);
		return (0);
	}
	return (1);
}

int		ft_init_shaders(t_env *env)
{
	if (!ft_init_vertex_shader(env))
		return (0);
	if (!ft_init_fragment_shader(env))
	{
		glDeleteShader(env->vertex_shader);
		return (0);
	}
	if (!ft_init_shader_program(env))
	{
		glDeleteShader(env->vertex_shader);
		glDeleteShader(env->fragment_shader);
		return (0);
	}
	glUseProgram(env->shader_program);
	glDeleteShader(env->vertex_shader);
	glDeleteShader(env->fragment_shader);
	return (1);
}

float		degtorad(float deg)
{
	return (deg * M_PI / 180);
}

float		radtodeg(float rad)
{
	return (rad * 180 / M_PI);
}

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

void	ft_set_matrix(t_env *env)
{
	ft_matrix_set_identity(&env->mvp.trans);
	ft_matrix_set_identity(&env->mvp.rot);
	ft_matrix_set_scale(&env->mvp.scale, 1);

	env->mvp.uni_trans = glGetUniformLocation(env->shader_program, "trans");
	glUniformMatrix4fv(env->mvp.uni_trans, 1, GL_FALSE, (float*)&env->mvp.trans);
	env->mvp.uni_rot = glGetUniformLocation(env->shader_program, "rot");
	glUniformMatrix4fv(env->mvp.uni_rot, 1, GL_FALSE, (float*)&env->mvp.rot);
	env->mvp.uni_scale = glGetUniformLocation(env->shader_program, "scale");
	glUniformMatrix4fv(env->mvp.uni_scale, 1, GL_FALSE, (float*)&env->mvp.scale);

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

void	ft_init_camera(t_cam *cam)
{
	cam->front = vec_normalize(vec_set(0, 0, -1));
	cam->up = vec_normalize(vec_set(0, 1, 0));
	cam->right = vec_normalize(vec_set(1, 0, 0));
	cam->scale = 1;
}

void	ft_init_cursor(t_env *env)
{
	glfwGetCursorPos(env->win, &env->curs.xpos, &env->curs.ypos);
	env->curs.mode = NORMAL;
}

int		ft_init(t_env *env)
{
	(void)env;
	if (!ft_init_glfw())
		return (0);
	if (!ft_init_window(env))
		return (0);
	glfwSetKeyCallback(env->win, key_callback);
	glfwSetScrollCallback(env->win, scroll_callback);
	glfwSetMouseButtonCallback(env->win, mouse_click_callback);
	ft_display_infos();
	ft_init_shaders(env);
	ft_create_buffers(env);
	ft_init_camera(&env->cam);
	ft_set_matrix(env);
	ft_init_cursor(env);
//		glEnable(GL_DEPTH_TEST); // enable depth-testing
//		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	return (1);
}
