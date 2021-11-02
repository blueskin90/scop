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
		virtual ~Camera();
		Camera&	operator=(Camera const &rhs);

		void	move(Vector	dir);
		void	rotate(Vector axis, float angle);
        void    roll(float angle);
        void    pitch(float angle);
        void    yawn(float angle);

		void	bindToProgram(GLuint program);
		void	update(void);

		Vector	pos;
		Vector	xaxis;
		Vector	yaxis;
		Vector	zaxis;
		Matrix	worldToCam;

	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Camera const &arg);
 
#endif // CAMERA_HPP

