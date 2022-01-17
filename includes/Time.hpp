#ifndef TIME_HPP
#define TIME_HPP
 
#include <iostream>
 
#include "glincludes.hpp"


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

