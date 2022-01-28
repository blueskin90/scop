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

	Shader vertexShader;
	Shader fragmentShader;
	Shader geometryShader;

	vertexShader.setPath(VERTEX_SHADER_PATH);
	fragmentShader.setPath(FRAGMENT_SHADER_PATH);
	vertexShader.compile(GL_VERTEX_SHADER);
	fragmentShader.compile(GL_FRAGMENT_SHADER);
	geometryShader.setPath(GEOMETRY_SHADER_PATH);
	geometryShader.compile(GL_GEOMETRY_SHADER);
	// ici try catch de la compile



	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, vertexShader.id);
	glAttachShader(shader_programme, geometryShader.id);
	glAttachShader(shader_programme, fragmentShader.id);
	glLinkProgram(shader_programme);

	// marked for deletion after program is deleted
	glDeleteShader(vertexShader.id);
	glDeleteShader(geometryShader.id);
	glDeleteShader(fragmentShader.id);


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

	glDeleteProgram(shader_programme);
	// penser a unbind les buffers
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

void	test_init_callbacks(t_env *env)
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(env->win, key_callback);
	glfwSetCursorPosCallback(env->win, mouse_move_callback);
	glfwSetMouseButtonCallback(env->win, mouse_button_callback);
    //glfwSetFrameBufferSizeCallback to be notified when the size change
}

int		test_init(t_env *env)
{
	if (!init_glfw(env))
		return (0);
	if (!init_main_window(env)) // create windows before assigning callbacks 
		return (0);
	test_init_callbacks(env);
	env->mode = NONE;
    env->time.init();
	return (1);
}

int		main(int ac, char **av)
{
	t_env	env;

	if (!parsing(&env, ac, av))
		return (1);
	if (!test_init(&env))
		return (1);
	//display_infos();
	main_loop(&env);
	clean_exit(&env);
	return (0);
}
