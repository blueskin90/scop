#include "scop.hpp"

void error_callback(int error, const char* description)
{
	std::cerr << "Error " << error << ": " << description << std::endl;
}

void	mouse_move_callback(GLFWwindow *win, double xpos, double ypos)
{
	t_env	*env;

	env = (t_env*)glfwGetWindowUserPointer(win);
	env->mouse.cursor_position_callback(win, xpos, ypos);
    if (env->mode == MOVEXZ)
        env->obj._model.move(Vector(env->mouse.diff.x, 0, env->mouse.diff.y) * env->time.deltaTime);
    if (env->mode == ROTATEXY)
    {
        env->obj._model.rotate(env->cam.xaxis, env->mouse.diff.y);
        env->obj._model.rotate(env->cam.yaxis, env->mouse.diff.x);
    }
	if (env->mode == MOVEXY)
        env->obj._model.move(Vector(env->mouse.diff.x, -env->mouse.diff.y, 0) * env->time.deltaTime);
    if (env->mode == ROTATEXZ)
    {
        env->obj._model.rotate(env->cam.zaxis, env->mouse.diff.x);
        env->obj._model.rotate(env->cam.xaxis, env->mouse.diff.y);
    }
    if (env->mode == ROTATEXYSELF)
    {
        env->obj._model.rotate(env->obj._model.xaxis, env->mouse.diff.y);
        env->obj._model.rotate(env->obj._model.yaxis, env->mouse.diff.x);
    }
    if (env->mode == ROTATEXZSELF)
    {
        env->obj._model.rotate(env->cam.zaxis, env->mouse.diff.x);
        env->obj._model.rotate(env->cam.xaxis, env->mouse.diff.y);
    }
}

void	mouse_button_callback(GLFWwindow *win, int button, int action, int mods)
{
	t_env	*env;

	env = (t_env*)glfwGetWindowUserPointer(win);
	env->mouse.button_pressed_callback(win, button, action, mods);
//	std::cout << "key : " << button << " action: " << action << " mods: " << mods << std::endl;
    if (env->mode == NONE && action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            env->mode = (mods & GLFW_MOD_CONTROL) ? ROTATEXZ : ROTATEXY; // mods == 2 == ctrl
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            env->mode = (mods & GLFW_MOD_CONTROL ) ? MOVEXY : MOVEXZ;
		else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
			env->mode = (mods & GLFW_MOD_CONTROL ) ? ROTATEXZSELF : ROTATEXYSELF;

    }
    else if (action == GLFW_RELEASE)
    {
        if ((env->mode == ROTATEXY || env->mode == ROTATEXZ) && button == GLFW_MOUSE_BUTTON_LEFT)
            env->mode = NONE;
        else if ((env->mode == MOVEXZ || env->mode == MOVEXY) && button == GLFW_MOUSE_BUTTON_RIGHT)
            env->mode = NONE;
        else if ((env->mode == ROTATEXYSELF || env->mode == ROTATEXZSELF) && button == GLFW_MOUSE_BUTTON_MIDDLE)
            env->mode = NONE;

    }
}

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)mods;
	(void)scancode;
	t_env *env;

	Vector	direction(0, 0, 0);

	env = (t_env*)glfwGetWindowUserPointer(window);
	//std::cout << "key : " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		direction += Vector(0, 0, 1);	
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		direction += Vector(-1, 0, 0);	
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		direction += Vector(0, 0, -1);	
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
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
	if (key == GLFW_KEY_LEFT_CONTROL)
	{
		if (action == GLFW_PRESS)
		{
			if (env->mode == ROTATEXY)
				env->mode = ROTATEXZ;
			else if (env->mode == MOVEXZ)
				env->mode = MOVEXY;
			else if (env->mode == ROTATEXYSELF)
				env->mode = ROTATEXZSELF;
		}
		else if (action == GLFW_RELEASE)
		{
			if (env->mode == ROTATEXZ)
				env->mode = ROTATEXY;
			else if (env->mode == MOVEXY)
				env->mode = MOVEXZ;
			else if (env->mode == ROTATEXYSELF)
				env->mode = ROTATEXZSELF;

		}
	}
}
