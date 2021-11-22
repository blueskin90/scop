#include "Time.hpp"
 
Time	&Time::operator=(Time const &rhs)
{
	(void)rhs;
	return (*this);
//assignation operator
}
 
Time::Time()
{
//constructor 
}
 
 
Time::Time(Time const &src)
{
	(void)src;
//copy constructor
}
 
 
Time::~Time()
{
//destructor
}
 
 
std::ostream&	operator<<(std::ostream &output, Time const &rhs)
{
	(void)rhs;
	return (output);
//redirection operator
}

