/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:36:21 by toliver           #+#    #+#             */
/*   Updated: 2020/08/23 16:02:15 by toliver          ###   ########.fr       */
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
	glUniformMatrix4fv(env->mvp.uni_persp, 1, GL_FALSE, (float*)&env->mvp.persp);
	glUniformMatrix4fv(env->mvp.uni_local, 1, GL_FALSE, (float*)&env->mvp.local_transform);
	glUniformMatrix4fv(env->mvp.uni_obj_to_world, 1, GL_FALSE, (float*)&env->mvp.obj_to_world);
}

void	ft_move_camera(t_env *env)
{
	t_vec4	vec;

	vec = vec_set(0, 0, 0);
	if (env->curs.mode == MIDDLE_CLICK)
	{
		vec = vec_add(vec, vec_mul(env->cam.xaxis, -env->curs.xdiff));
		vec = vec_add(vec, vec_mul(env->cam.yaxis, env->curs.ydiff));
	}
	vec = vec_mul(vec, env->delta_time * env->cam.scale);
	ft_matrix_set_tran(&env->mvp.trans, vec_opp(vec));
	env->mvp.obj_to_world = ft_matrix_mult_matrix(&env->mvp.obj_to_world, &env->mvp.trans);
}

void	ft_rotate_camera(t_env *env)
{
	float zangle = 0;
	float yangle = 0;
	float xangle = 0;
	t_mat4	total_rot;

	ft_matrix_set_identity(&total_rot);
	if (env->curs.mode == RIGHT_CLICK)
	{
		zangle += 1.0 * env->curs.xdiff * env->delta_time * SPEED;
		ft_matrix_set_rot(&env->mvp.rot, env->cam.zaxis, zangle);
		total_rot = ft_matrix_mult_matrix(&total_rot, &env->mvp.rot);
	}
	else if (env->curs.mode == LEFT_CLICK)
	{
		yangle = 1.0 * env->curs.xdiff * env->delta_time * SPEED;
		ft_matrix_set_rot(&env->mvp.rot, env->cam.yaxis, yangle);
		total_rot = ft_matrix_mult_matrix(&total_rot, &env->mvp.rot);

		xangle = 1.0 * env->curs.ydiff * env->delta_time * SPEED;
		ft_matrix_set_rot(&env->mvp.rot, vec_opp(env->cam.xaxis), xangle);
		total_rot = ft_matrix_mult_matrix(&total_rot, &env->mvp.rot);
	}
	env->mvp.obj_to_world = ft_matrix_mult_matrix(&env->mvp.obj_to_world, &total_rot);
//	env->obj.yaxis = vec_normalize(ft_matrix_mult_vec(&total_rot, env->obj.yaxis));
//	env->obj.zaxis = vec_normalize(ft_matrix_mult_vec(&total_rot, env->obj.zaxis));
//	env->obj.xaxis = vec_normalize(ft_matrix_mult_vec(&total_rot, env->obj.xaxis));
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

void	ft_rotate_object(t_env *env)
{
	t_mat4	mat;

	if (env->obj.rotating == 1)
	{
		ft_matrix_set_rot(&mat, env->obj.yaxis, env->obj.rotspeed * env->delta_time);
		env->mvp.local_transform = ft_matrix_mult_matrix(&mat, &env->mvp.local_transform);
		env->obj.yaxis = vec_normalize(ft_matrix_mult_vec(&env->mvp.local_transform, env->obj.yaxis));
		env->obj.xaxis = vec_normalize(ft_matrix_mult_vec(&env->mvp.local_transform, env->obj.yaxis));
		env->obj.zaxis = vec_normalize(ft_matrix_mult_vec(&env->mvp.local_transform, env->obj.yaxis));
	}
}

void	ft_test(t_env *env)
{	
	int width;
	int	height;


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    // -----------
	glfwSetTime(0);
	glfwSwapInterval(1);

    while (!glfwWindowShouldClose(env->win))
    {
		glfwGetFramebufferSize(env->win, &width, &height);
		glViewport(0, 0, width, height);
		get_time(env);
		get_cursor(env);
		ft_move_camera(env);
		ft_rotate_camera(env);
		ft_rotate_object(env);
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
	
	ft_test(env);
	return ;
}

void	ft_close(t_env *env)
{
    glDeleteProgram(env->shader_program);
	ft_glfw_close(env);
	ft_free_env(env);
}

int		ft_parsing(t_env *env, int ac, char **av)
{
	env->name = av[0];
	if (ac != 2) // changer si je parse plus d'un fichier
	{
		ft_usage();
		return (0);
	}
	if (!(obj_parse(env, av[1])))
	{
		ft_free_env(env);
		return (0);
	}
	//ft_init_obj(env);
	return (1);
}

int		main(int ac, char **av)
{
	t_env	env;

	ft_bzero(&env, sizeof(t_env));
	ft_setenv(&env);
	if (!ft_parsing(&env, ac, av))
		return (-1);
	ft_init(&env);
	ft_loop(&env);	
	ft_close(&env);
	return (0);
}
