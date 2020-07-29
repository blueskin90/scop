/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 17:25:02 by toliver           #+#    #+#             */
/*   Updated: 2020/07/29 18:51:27 by toliver          ###   ########.fr       */
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

void	ft_move_camera(int key, t_env *env)
{
	t_vec4	vec;

	(void)key;
	vec = vec_set(0, 0, 0);
	if (glfwGetKey(env->win, GLFW_KEY_LEFT) == GLFW_PRESS)
		vec.x -= 1;
	if (glfwGetKey(env->win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		vec.x += 1;
	if (glfwGetKey(env->win, GLFW_KEY_UP) == GLFW_PRESS)
		vec.y += 1;
	if (glfwGetKey(env->win, GLFW_KEY_DOWN) == GLFW_PRESS)
		vec.y -= 1;
	vec = vec_normalize(vec);
	env->cam.pos = vec_add(env->cam.pos, vec_mul(vec_normalize(vec), env->delta_time));
}

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	else if ((action == GLFW_PRESS || action == GLFW_REPEAT)
			&& (key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT
			|| key == GLFW_KEY_UP || key == GLFW_KEY_DOWN))
		ft_move_camera(key, ft_getenv());
}


