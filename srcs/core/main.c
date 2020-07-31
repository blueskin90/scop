/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:36:21 by toliver           #+#    #+#             */
/*   Updated: 2020/07/31 07:10:55 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void	ft_free_env(t_env *env)
{
	// free env;
	free(env->obj.name);
	free(env->obj.vertices);
	free(env->obj.faces);
}

void	ft_glfw_close(t_env *env)
{
	(void)env;
	if (env->win)
		glfwDestroyWindow(env->win);
	glfwTerminate();
}

void	ft_matrix_use(t_env *env)
{
// graphic pipeline -> move obj so it's centered around it's axis
// apply rotations to the object
// move object to world pos (depending on camera)
// perspective matrix
	ft_matrix_set_tran(&env->mvp.trans, vec_opp(env->cam.pos));
	glUniformMatrix4fv(env->mvp.uni_trans, 1, GL_FALSE, (float*)&env->mvp.trans);
//	ft_matrix_set_rot(&env->mvp.rot, env->cam.front, angle);
	glUniformMatrix4fv(env->mvp.uni_rot, 1, GL_FALSE, (float*)&env->mvp.rot);
	ft_matrix_set_scale(&env->mvp.scale, env->cam.scale);
	glUniformMatrix4fv(env->mvp.uni_scale, 1, GL_FALSE, (float*)&env->mvp.scale);
}

void	ft_move_camera(t_env *env)
{
	t_vec4	vec;

	vec = vec_set(0, 0, 0);
	if (env->curs.mode == MIDDLE_CLICK)
	{
		vec = vec_add(vec, vec_mul(env->cam.right, -env->curs.xdiff));
		vec = vec_add(vec, vec_mul(env->cam.up, env->curs.ydiff));
	}
	env->cam.pos = vec_add(env->cam.pos, vec_mul(vec, env->delta_time * env->cam.scale));
}

void	ft_rotate_camera(t_env *env)
{
	static float zangle = 0;
	static float yangle = 0;
	static float xangle = 0;

	if (env->curs.mode == RIGHT_CLICK)
	{
		zangle += 1.0 * env->curs.xdiff * env->delta_time * SPEED;
		ft_matrix_set_rot(&env->mvp.rot, env->obj.zaxis, zangle);
	}
	else if (env->curs.mode == LEFT_CLICK && abs(env->curs.xdiff) > abs(env->curs.ydiff))
	{
		yangle += 1.0 * env->curs.xdiff * env->delta_time * SPEED;
		ft_matrix_set_rot(&env->mvp.rot, env->obj.yaxis, yangle);
	}
	else if (env->curs.mode == LEFT_CLICK && abs(env->curs.xdiff) < abs(env->curs.ydiff))
	{
		xangle += 1.0 * env->curs.ydiff * env->delta_time * SPEED;
		ft_matrix_set_rot(&env->mvp.rot, env->obj.xaxis, xangle);
	}
}

void	get_cursor(t_env *env)
{
	int		xdiff;
	int		ydiff;
	double	xpos;
	double	ypos;

	glfwGetCursorPos(env->win, &xpos, &ypos);
	env = ft_getenv();
	xdiff = xpos - env->curs.xpos;
	ydiff = ypos - env->curs.ypos;
	env->curs.xdiff = xdiff;
	env->curs.ydiff = ydiff;
	env->curs.xpos = xpos;
	env->curs.ypos = ypos;
}

void	get_time(t_env *env)
{
	env->delta_time = (float)glfwGetTime();
	glfwSetTime(0);
}

void	ft_test(t_env *env)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    // -----------
	glfwSetTime(0);
    while (!glfwWindowShouldClose(env->win))
    {
		get_time(env);
		get_cursor(env);
		ft_move_camera(env);
		ft_rotate_camera(env);
		ft_matrix_use(env);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(env->shader_program);
        glBindVertexArray(env->vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, env->obj.triangles_nbr * 3, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(env->win);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &env->vao);
    glDeleteBuffers(1, &env->vbo);
    glDeleteBuffers(1, &env->ebo);
}

void	ft_loop(t_env *env)
{
	int width;
	int	height;

	double time = glfwGetTime();
	(void)time;

	glfwGetFramebufferSize(env->win, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapInterval(1);


	ft_test(env);
	return ;
	while (!glfwWindowShouldClose(env->win))
	{
		glfwSwapBuffers(env->win);
		glfwPollEvents();
		// Keep running
	}
}

void	ft_close(t_env *env)
{
    glDeleteProgram(env->shader_program);
	ft_glfw_close(env);
	ft_free_env(env);
}

int		main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	ft_setenv(&env);
	env.name = av[0];
	if (ac != 2) // changer si je parse plus d'un fichier
	{
		ft_usage();
		return (-1);
	}
	if (!(obj_parse(&env, av[1])))
	{
		ft_free_env(&env);
		return (-1);
	}
	ft_init(&env);
	ft_loop(&env);	
	ft_close(&env);
	return (0);
}
