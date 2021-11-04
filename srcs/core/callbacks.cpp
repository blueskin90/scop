#include "scop.hpp"

void error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << ": " << description << std::endl;
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	t_env *env;

	Vector	direction(0, 0, 0);

	env = (t_env*)glfwGetWindowUserPointer(window);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		direction += Vector(0, 0, 1);	
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		direction += Vector(-1, 0, 0);	
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		direction += Vector(0, 0, -1);	
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		direction += Vector(1, 0, 0);	
	if (key == GLFW_KEY_D || GLFW_KEY_S || GLFW_KEY_A || GLFW_KEY_W)
	{
		direction.normalize();
		direction *= 0.1;
		env->cam.move(direction);
	}
    if (key == GLFW_KEY_LEFT)
        env->cam.pitch(1);
    if (key == GLFW_KEY_RIGHT)
        env->cam.pitch(-1);
    if (key == GLFW_KEY_UP)
        env->cam.yawn(1);
    if (key == GLFW_KEY_DOWN)
        env->cam.yawn(-1);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		env->obj.toggleRotation();
}
