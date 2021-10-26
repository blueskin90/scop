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
	std::cout << env->obj << std::endl;
	return (1);
}

int		main_loop(t_env *env)
{
   	while (!glfwWindowShouldClose(env->win))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(env->win);

        /* Poll for and process events */
        glfwPollEvents();
    }
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
