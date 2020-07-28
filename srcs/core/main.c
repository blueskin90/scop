/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toliver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 11:36:21 by toliver           #+#    #+#             */
/*   Updated: 2020/07/28 20:16:40 by toliver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void error_callback(int error, const char* description)
{
	ft_dprintf(2, "Error %d: %s\n", error, description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

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
		return 1;
	}
	glfwMakeContextCurrent(window);

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	/* OTHER STUFF GOES HERE NEXT */
	// close GL context and any other GLFW resources
	glfwTerminate();
	return (0);
}

void	ft_usage(void)
{
	ft_printf("usage: ./scop [-%s] file.obj\n", FLAGS);
}

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
	glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4) * env->obj.vertices_nbr, env->obj.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t_vec3int) * env->obj.triangles_nbr, env->obj.triangle_indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(t_vec4), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glGenBuffers(1, &(env->vao));
	return (1);
}

int		ft_init_vertex_shader(t_env *env)
{
	int  		success;
	char		buf[513];
	const char	*vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1);\n"
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

	
	// still have to link buffers, but dont know how to do it T-T
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	//	glEnable(GL_DEPTH_TEST); // enable depth-testing
	//	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"


	return (1);
}
/*
void	ft_test(t_env *env)
{
	glGenVertexArrays(1, &env->vao);
    glGenBuffers(1, &env->vbo);
    glGenBuffers(1, &env->ebo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(env->vao);

    glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(t_vec4) * env->obj.vertices_nbr, env->obj.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(t_vec3int) * env->obj.triangles_nbr, env->obj.triangle_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(env->win))
    {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(env->shader_program);
        glBindVertexArray(env->vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, env->obj.triangles_nbr, GL_UNSIGNED_INT, 0);
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
    glDeleteProgram(env->shader_program);
}


void	ft_test2(t_env *env)
{
    while (!glfwWindowShouldClose(env->win))
    {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(env->shader_program);
        glBindVertexArray(env->vao);
		glDrawElements(GL_TRIANGLES, env->obj.triangles_nbr, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(env->win);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &env->vao);
    glDeleteBuffers(1, &env->vbo);
    glDeleteProgram(env->shader_program);
}
*/


void	ft_test(t_env *env)
{

    glGenVertexArrays(1, &env->vao);
    glGenBuffers(1, &env->vbo);
    glGenBuffers(1, &env->ebo);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(env->vao);

    glBindBuffer(GL_ARRAY_BUFFER, env->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * env->obj.vertices_nbr, env->obj.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, env->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * env->obj.triangles_nbr, env->obj.triangle_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(env->win))
    {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(env->shader_program);
        glBindVertexArray(env->vao); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
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
	t_env	*env;

	env = ft_getenv();
	env->name = av[0];
	if (ac != 2) // changer si je parse plus d'un fichier
	{
		ft_usage();
		return (-1);
	}
	if (!(obj_parse(env, av[1])))
	{
		ft_free_env(env);
		return (-1);
	}
	ft_init(env);
	ft_loop(env);	
	ft_close(env);
	return (0);
}
