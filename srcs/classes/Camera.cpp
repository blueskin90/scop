#include "Camera.hpp"
 
Camera	&Camera::operator=(Camera const &rhs)
{
	(void)rhs;
	return (*this);
}
 
Camera::Camera()
{
//constructor 
}
 
 
Camera::Camera(Camera const &src)
{
	(void)src;
}
 
 
Camera::~Camera()
{
//destructor
}
 
 
std::ostream&	operator<<(std::ostream &output, Camera const &lhs)
{
	(void)lhs;
	return (output);
}

