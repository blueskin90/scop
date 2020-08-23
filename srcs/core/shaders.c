/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 14:27:34 by toliver           #+#    #+#             */
/*   Updated: 2020/08/23 16:05:17 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

int		ft_init_vertex_shader(t_env *env)
{
	int  		success;
	char		buf[513];
	const char	*vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec4 aPos;\n"
	"uniform mat4 local;\n"
	"uniform mat4 obj_to_world;\n"
	"uniform mat4 persp;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = persp * obj_to_world * local * vec4(aPos.x, aPos.y, aPos.z, aPos.w);\n"
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
