#ifndef CAMERA_HPP
#define CAMERA_HPP
 
#include <iostream>
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Vector3int.hpp"

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h> // GLFW helper library


 
class Camera
{
	public:
		Camera();
		Camera(Camera const &src);
		virtual ~Camera()
		Camera&	operator=(Camera const &rhs);
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Camera const &arg);
 
#endif // CAMERA_HPP

