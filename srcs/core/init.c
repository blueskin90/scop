/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:30:39 by toliver           #+#    #+#             */
/*   Updated: 2020/08/23 16:05:17 by toliver          ###   ########.fr       */
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

void	ft_set_matrix(t_env *env)
{
	ft_matrix_set_identity(&env->mvp.trans);
	ft_matrix_set_identity(&env->mvp.rot);
	ft_matrix_set_scale(&env->mvp.scale, 1);
	ft_matrix_set_identity(&env->mvp.local_transform);
	ft_matrix_set_identity(&env->mvp.obj_to_world);
	ft_matrix_set_identity(&env->mvp.persp);


	env->mvp.uni_local = glGetUniformLocation(env->shader_program, "local");
	glUniformMatrix4fv(env->mvp.uni_local, 1, GL_FALSE, (float*)&env->mvp.local_transform);

	env->mvp.uni_obj_to_world = glGetUniformLocation(env->shader_program, "obj_to_world");
	glUniformMatrix4fv(env->mvp.uni_obj_to_world, 1, GL_FALSE, (float*)&env->mvp.obj_to_world);

	env->mvp.uni_persp = glGetUniformLocation(env->shader_program, "persp");
	glUniformMatrix4fv(env->mvp.uni_persp, 1, GL_FALSE, (float*)&env->mvp.persp);
}

void	ft_init_cursor(t_env *env)
{
	glfwGetCursorPos(env->win, &env->curs.xpos, &env->curs.ypos);
	env->curs.mode = NORMAL;
}

void	ft_init_obj(t_obj *obj)
{
	obj->zaxis = vec_set(0, 0, -1);
	obj->yaxis = vec_set(0, 1, 0);
	obj->xaxis = vec_set(1, 0, 0);
	obj->rotspeed = 10;
}

void	ft_init_cam(t_cam *cam)
{
	cam->zaxis = vec_set(0, 0, -1);
	cam->yaxis = vec_set(0, 1, 0);
	cam->xaxis = vec_set(1, 0, 0);
	cam->scale = 1;
}

void	ft_init_callbacks(t_env *env)
{
	glfwSetKeyCallback(env->win, key_callback);
	glfwSetScrollCallback(env->win, scroll_callback);
	glfwSetMouseButtonCallback(env->win, mouse_click_callback);
}

int		ft_init(t_env *env)
{
	ft_init_cam(&env->cam);
	ft_init_obj(&env->obj);
	if (!ft_init_glfw())
		return (0);
	if (!ft_init_window(env))
		return (0);
	ft_init_callbacks(env);
//	ft_display_infos();
	ft_init_shaders(env);
	ft_create_buffers(env);
	ft_set_matrix(env);
	ft_init_cursor(env);
//		glEnable(GL_DEPTH_TEST); // enable depth-testing
//		glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	return (1);
}
