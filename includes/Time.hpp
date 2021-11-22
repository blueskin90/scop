#ifndef TIME_HPP
#define TIME_HPP
 
#include <iostream>
 
class Time
{
	public:
		Time();
		Time(Time const &src);
		virtual ~Time();
		Time&	operator=(Time const &rhs);
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Time const &rhs);
 
#endif // TIME_HPP

