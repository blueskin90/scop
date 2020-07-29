/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:30:39 by toliver           #+#    #+#             */
/*   Updated: 2020/07/29 23:07:06 by toliver          ###   ########.fr       */
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
    "void main()\n"
    "{\n"
    "   gl_Position = trans * rot * vec4(aPos.x, aPos.y, aPos.z, aPos.w);\n"
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
	ft_matrix_set_identity(mat);
	angle = degtorad(angle);
	(void)mat;
	(void)axis;
	(void)angle;
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

	env->mvp.uni_trans = glGetUniformLocation(env->shader_program, "trans");
	glUniformMatrix4fv(env->mvp.uni_trans, 1, GL_FALSE, (float*)&env->mvp.trans);
	env->mvp.uni_rot = glGetUniformLocation(env->shader_program, "rot");
	glUniformMatrix4fv(env->mvp.uni_rot, 1, GL_FALSE, (float*)&env->mvp.rot);
}

void	ft_init_camera(t_cam *cam)
{
	cam->front.z = -1;
	cam->up.y = 1;
	cam->right.x = 1;
}

int		ft_init(t_env *env)
{
	(void)env;
	if (!ft_init_glfw())
		return (0);
	if (!ft_init_window(env))
		return (0);
	glfwSetKeyCallback(env->win, key_callback);
	ft_display_infos();
	ft_init_shaders(env);
	ft_create_buffers(env);
	ft_init_camera(&env->cam);
	ft_set_matrix(env);

	
	//	glEnable(GL_DEPTH_TEST); // enable depth-testing
	//	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"


	return (1);
}
