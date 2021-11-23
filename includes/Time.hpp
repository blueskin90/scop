#ifndef TIME_HPP
#define TIME_HPP
 
#include <iostream>
 

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h> // GLFW helper library


class Time
{
	public:
		Time();
		Time(Time const &src);
		virtual ~Time();
		Time&	operator=(Time const &rhs);
        void    update(void);
        void    init(void);

        double deltaTime;
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Time const &rhs);
 
#endif // TIME_HPP

