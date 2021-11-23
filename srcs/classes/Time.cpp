#include "Time.hpp"
 
Time	&Time::operator=(Time const &rhs)
{
    this->deltaTime = rhs.deltaTime;
	return (*this);
//assignation operator
}
 
Time::Time(): deltaTime(0)
{
//constructor 
}
 
 
Time::Time(Time const &src)
{
    this->deltaTime = src.deltaTime;
//copy constructor
}
 
void    Time::update(void)
{
    this->deltaTime = glfwGetTime();
    glfwSetTime(0);
}

void    Time::init(void)
{
    glfwSetTime(0);
}
 
Time::~Time()
{
//destructor
}
 
 
std::ostream&	operator<<(std::ostream &output, Time const &rhs)
{
    output << rhs.deltaTime;
	return (output);
//redirection operator
}

