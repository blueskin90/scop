#include "scop.hpp"

int		init_main_window(t_env *env)
{
	env->winx = WIDTH;
	env->winy = HEIGHT;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
 	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
 	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 
    env->win = glfwCreateWindow(env->winx, env->winy, "Scop", NULL, NULL);
 	if (!env->win) {
    	fprintf(stderr, "ERROR: could not open window with GLFW3\n");
    	glfwTerminate();
    	return (0);
  	}
  	glfwMakeContextCurrent(env->win);
	glfwSetWindowUserPointer(env->win, (void*)env); // ici on set le pointer de la window sur l'env
	return (1);
}

void	init_callbacks(t_env *env)
{
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(env->win, key_callback);
    //glfwSetFrameBufferSizeCallback to be notified when the size change
}

int		init_glfw(t_env *env)
{
	(void)env;
    if (!glfwInit())
	{
		std::cerr << "Couldn't inititalize GLFW" << std::endl;
		return (0);
	}
	return (1);
}

int		init(t_env *env)
{
	if (!init_glfw(env))
		return (0);
	if (!init_main_window(env)) // create windows before assigning callbacks 
		return (0);
	init_callbacks(env);
	return (1);
}
