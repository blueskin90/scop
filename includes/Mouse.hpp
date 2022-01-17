#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <iostream>

#include <iostream>
#include "Vector.hpp"

#include <vector>

#include "glincludes.hpp"

#define LEFT_MOUSE_BUTTON 0
#define RIGHT_MOUSE_BUTTON 1
#define MIDDLE_MOUSE_BUTTON 2

class Button
{
	public:
		Button(void);
		virtual ~Button(void);
		void	press(void);
		void	release(void);

		bool	is_pressed;
		bool	was_pressed;
		bool	was_released;

		void	update(void);
};

class Mouse
{
	public:
		Mouse(void);
		Mouse(Mouse const &src);
		virtual ~Mouse(void);
		Mouse&	operator=(Mouse const &rhs);

		void	cursor_position_callback(GLFWwindow *win, double xpos, double ypos);
		void	button_pressed_callback(GLFWwindow *win, int button, int action, int mods);
		void	update(void);

		Vector	pos;
		Vector	diff;
		Button	button[3];
	protected:
	private:
};

std::ostream&	operator<<(std::ostream &output,Mouse const &arg);

#endif // MOUSE_HPP

