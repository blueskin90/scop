/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:35:10 by toliver           #+#    #+#             */
/*   Updated: 2021/10/28 19:27:07 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include "Vector.hpp"
#include "Obj.hpp"
#include "Matrix.hpp"
#include "Camera.hpp"

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h> // GLFW helper library

#define WIDTH 800
#define HEIGHT 600

typedef struct		s_env
{
	Obj				obj;
	Camera			cam;
	GLFWwindow		*win;
	int				winx;
	int				winy;
}					t_env;

/*
** CALLBACKS FUNCTIONS
*/

void	error_callback(int error, const char* description);
void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

/*
** INIT FUNCTIONS
*/

int		init(t_env *env);
int		init_glfw(t_env *env);
void	init_callbacks(t_env *env);
int		init_main_window(t_env *env);

#endif
