/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:36:21 by toliver           #+#    #+#             */
/*   Updated: 2020/07/29 18:39:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
/*
int	ft_glinit()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 0;
	}
	glfwMakeContextCurrent(window);
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	return (1);
}
*/

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
	ft_matrix_set_tran(&env->mvp.trans, vec_opp(env->cam.pos));
	glUniformMatrix4fv(env->mvp.uni_trans, 1, GL_FALSE, (float*)&env->mvp.trans);
}

void	ft_test(t_env *env)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
	glfwSetTime(0);
    while (!glfwWindowShouldClose(env->win))
    {
		env->delta_time = (float)glfwGetTime();
		glfwSetTime(0);
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
