#include "Camera.hpp"
 
Camera	&Camera::operator=(Camera const &rhs)
{
	(void)rhs;
	return (*this);
}
 
Camera::Camera(void): pos(0, 0, 0), xaxis(1, 0, 0), yaxis(0, 1, 0), zaxis(0, 0, -1) 
{
	this->worldToCam.init_identity();
//constructor 
}
 
 
Camera::Camera(Camera const &src)
{
	this->pos = src.pos;
	this->xaxis = src.xaxis;
	this->yaxis = src.yaxis;
	this->zaxis = src.zaxis;
	this->worldToCam = src.worldToCam;
}
 
 
Camera::~Camera()
{
//destructor
}
 
void	Camera::move(Vector dir)
{
	(void)dir;
}

void	Camera::rotate(Vector axis, float angle)
{
	(void)axis;
	(void)angle;
}
 
std::ostream&	operator<<(std::ostream &output, Camera const &lhs)
{
	std::cout << "Camera\n\tPos: " << lhs.pos << std::endl;
	std::cout << "\t  xaxis: " << lhs.xaxis << std::endl;
	std::cout << "\t  yaxis: " << lhs.yaxis << std::endl;
	std::cout << "\t  zaxis: " << lhs.zaxis << std::endl;
	std::cout << lhs.worldToCam << std::endl;
	return (output);
}

