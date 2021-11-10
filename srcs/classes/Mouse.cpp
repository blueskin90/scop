#include "Mouse.hpp"

Button::Button(void): is_pressed(false), was_pressed(false), was_released(false)
{
}

Button::~Button(void)
{
}

void	Button::press(void)
{
	this->is_pressed = true;
	this->was_pressed = true;
	this->was_released = false;
}

void	Button::release(void)
{
	this->is_pressed = false;
	this->was_pressed = false;
	this->was_released = true;
}

void	Button::update(void)
{
	if (this->was_pressed)
	{
		this->was_pressed = false;
	}
	if (this->was_released)
	{
		this->was_released = false;
	}
}


void	Mouse::update(void)
{
	for (int i = 0; i < 3; i++)
	{
		this->button[i].update();
	}
}

Mouse	&Mouse::operator=(Mouse const &rhs)
{
	this->pos = rhs.pos;
	this->diff = rhs.diff;
	return (*this);
}

Mouse::Mouse(void): pos(Vector(0, 0, 0)), diff(Vector(0,0,0))
{
	for (int i = 0; i < 3; i++)
	{
		this->button[i].is_pressed = false;
		this->button[i].was_pressed = false;
	}
}


Mouse::Mouse(Mouse const &src)
{
	this->pos = src.pos;
	this->diff = src.diff;
	//copy constructor
}

void	Mouse::cursor_position_callback(GLFWwindow *win, double xpos, double ypos)
{
	(void)win;
	this->diff = Vector(xpos, ypos, 0) - this->pos;
	this->pos.x = xpos;
	this->pos.y = ypos;
	std::cout << *this << std::endl;
}

void	Mouse::button_pressed_callback(GLFWwindow* window, int button, int action, int mods)
{
	(void)mods;
	(void)window;
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS)
		{
			this->button[0].is_pressed = true;
			this->button[0].was_pressed = true;
		}
		else if (action == GLFW_RELEASE)
		{
			this->button[0].is_pressed = false;
			this->button[0].was_pressed = false;
		}
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{

	}
	else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
	{

	}	
}


Mouse::~Mouse(void)
{
	//destructor
}


std::ostream&	operator<<(std::ostream &output, Mouse const &lhs)
{
	output << "xpos: " << lhs.pos.x << " ypos: " << lhs.pos.y << std::endl;
	output << "xdiff: " << lhs.diff.x << " ydiff: " << lhs.diff.y << std::endl;
	return (output);
}

