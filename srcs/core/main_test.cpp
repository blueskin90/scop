#include "scop.hpp"

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h> // GLFW helper library
int		usage(void)
{
	std::cout << "usage: ./scop obj_file" << std::endl;
	return (1);
}

void error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << ": " << description << std::endl;
}

void	vecTest(void)
{

/*
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
*/

}

int		main(int ac, char **av)
{
	if (ac != 2)
		return (usage());
	(void)av;

	Obj myObj;

	myObj.setPath(av[1]);
	try{
		myObj.parseFile();
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}

	std::cout << myObj << std::endl;

    if (!glfwInit())
	{
		std::cerr << "Couldn't inititalize GLFW" << std::endl;
		return (1);
	}
	glfwSetErrorCallback(error_callback);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);
  if (!window) {
    fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);
                                  
  while(1){};
  	return (0);
}
