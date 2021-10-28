#include "Camera.hpp"
 
Camera	&Camera::operator=(Camera const &rhs)
{
	(void)rhs;
	return (*this);
}
 
Camera::Camera(void): pos(0, 0, 0), xaxis(1, 0, 0), yaxis(0, 1, 0), zaxis(0, 0, -1) 
{
	this->worldToCam.init_identity();
	this->worldToCam.set_name("worldToCam");
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
	this->pos += dir;

	this->worldToCam.init_translation(this->pos);
	std::cout << "cam pos " << this->pos << std::endl;
	std::cout << this->worldToCam << std::endl;
}

void	Camera::rotate(Vector axis, float angle)
{
	(void)axis;
	(void)angle;
}

void	Camera::bindToProgram(GLuint program)
{
	this->worldToCam.bind_to_program(program);
}

void	Camera::update(void)
{
	this->worldToCam.use();
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

