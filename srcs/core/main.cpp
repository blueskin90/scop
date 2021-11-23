#include "scop.hpp"

int		usage(void)
{
	std::cout << "usage: ./scop obj_file" << std::endl;
	return (0);
}

void	vecTest(void)
{
	Vector test;
	Vector test2(10, 5, -3.5);

	test[2] = 2;
	test.y = 10;
	test.x = 1;

	std::cout << test << std::endl;
	std::cout << test2 << std::endl;
	std::cout << test2 + test << std::endl;
	std::cout << test2 - test << std::endl;
	std::cout << test2 << std::endl;
	test2 -= test;
	std::cout << test2 << std::endl;
	test2 = test;
	std::cout << test2.norm() << std::endl;
	std::cout << test2.normalize() << std::endl;
	std::cout << test2.norm() << std::endl;
}

int		parsing(t_env *env, int ac, char **av)
{
	if (ac != 2)
		return (usage());
	env->obj.setPath(av[1]);
	try{
		env->obj.parseFile();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (0);
	}
//	std::cout << env->obj << std::endl;
	return (1);
}

int		main_loop(t_env *env)
{
	env->obj.genBuffers();
	const char* vertex_shader =
		"#version 400\n"
		"in vec3 vp;"
		"uniform mat4 worldToCam;"
		"uniform mat4 objToWorld;"
		"uniform mat4 persp;"
		"void main() {"
		"  gl_Position = persp * worldToCam * objToWorld * vec4(vp.x, vp.y, vp.z, 1.0);"
		"}";

	const char* fragment_shader =
		"#version 400\n"
		"out vec4 frag_colour;"
		"void main() {"
		"  frag_colour = vec4(0.5, 0.5, 1.0, 1.0);"
		"}";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);
// penser a verif la compile du shader
	env->cam.bindToProgram(shader_programme);
	env->obj.bindToProgram(shader_programme);

	Matrix persp;

	persp.init_perspective();
	persp.set_name("persp");
	persp.bind_to_program(shader_programme);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // render loop
    // -----------
	glfwSetTime(0);
	glfwSwapInterval(1);

	while(!glfwWindowShouldClose(env->win)) {
		// wipe the drawing surface clear
	   glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
        env->time.update();
		env->cam.update();
		env->obj.update();
		persp.use();

		env->obj.draw();
		env->mouse.update();
		// update other events like input handling 
		glfwPollEvents();
		// put the stuff we've been drawing onto the display
		glfwSwapBuffers(env->win);
	}
	/*
	   while (!glfwWindowShouldClose(env->win))
	   {
	// Render here 
	glClear(GL_COLOR_BUFFER_BIT);

	// Swap front and back buffers 
	glfwSwapBuffers(env->win);

	// Poll for and process events 
	glfwPollEvents();
	}
	*/
	return (1);
}

int		clean_exit(t_env *env)
{
	(void)env;
	glfwTerminate();
	return (1);
}

void	display_infos(void)
{
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
}

int		main(int ac, char **av)
{
	t_env	env;

	if (!parsing(&env, ac, av))
		return (1);
	if (!init(&env))
		return (1);
	//display_infos();
	main_loop(&env);
	clean_exit(&env);
	return (0);
}
