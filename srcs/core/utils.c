/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:25:02 by toliver           #+#    #+#             */
/*   Updated: 2020/08/23 15:54:03 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	ft_usage(void)
{
	ft_printf("usage: ./scop [-%s] file.obj\n", FLAGS);
}

void	error_callback(int error, const char* description)
{
	ft_dprintf(2, "Error %d: %s\n", error, description);
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	t_env		*env;

	env = ft_getenv();
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		env = ft_getenv();
		env->obj.rotating ^= 1;	
	}
	if (key == GLFW_KEY_KP_SUBSTRACT && action == GLFW_PRESS)
		env->obj.rotspeed = env->obj.rotspeed <= 0 ? 0 : env->obj.rotspeed - 1;
	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
		env->obj.rotspeed = env->obj.rotspeed == INT_MAX ? INT_MAX : env->obj.rotspeed + 1;
}

void	scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	t_env	*env;

	(void)window;
	(void)xoffset;
	env = ft_getenv();
	if (yoffset > 0)
	{
		env->cam.scale *= 1.1;
		ft_matrix_set_scale(&env->mvp.scale, 1.1);
	}
	else
	{
		ft_matrix_set_scale(&env->mvp.scale, 10.0 / 11.0);
		env->cam.scale *= (10.0 / 11.0);
	}
	env->mvp.obj_to_world = ft_matrix_mult_matrix(&env->mvp.obj_to_world, &env->mvp.scale);
}

void 	mouse_click_callback(GLFWwindow* window, int button, int action, int mods)
{
	t_env	*env;

	env = ft_getenv();
	(void)window;
	(void)mods;
	if (env->curs.mode == NORMAL && action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT)
			env->curs.mode = LEFT_CLICK;
		else if (button == GLFW_MOUSE_BUTTON_RIGHT)
			env->curs.mode = RIGHT_CLICK;
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			env->curs.mode = MIDDLE_CLICK;
	}
	else if (env->curs.mode == LEFT_CLICK && action == GLFW_RELEASE
			&& button == GLFW_MOUSE_BUTTON_LEFT)
		env->curs.mode = NORMAL;
	else if (env->curs.mode == RIGHT_CLICK && action == GLFW_RELEASE
			&& button == GLFW_MOUSE_BUTTON_RIGHT)
		env->curs.mode = NORMAL;
	else if (env->curs.mode == MIDDLE_CLICK && action == GLFW_RELEASE
			&& button == GLFW_MOUSE_BUTTON_MIDDLE)
		env->curs.mode = NORMAL;
}
