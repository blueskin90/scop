#ifndef MATRIX_HPP
#define MATRIX_HPP
 
# define GL_SILENCE_DEPRECATION
#include <iostream>
#include "Vector.hpp"
#include <iomanip>
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES 
#include <math.h>

class Matrix
{
	public:
		Matrix(void);
		Matrix(Matrix const &src);
		virtual ~Matrix();
		Matrix&	operator=(Matrix const &rhs);
		Matrix	operator*(Matrix const &rhs) const;
		Matrix&	operator*=(Matrix const &rhs);
		Vector	operator*(Vector const &rhs) const;

		void	init_identity(void);
		void	init_translation(Vector t);
		void	init_rotation(Vector axis, float angle);// angle en degres
		void	init_scale(float scale);
		void	init_perspective(void);

		void	set_name(std::string name);

		void	bind_to_program(GLuint program);
		void	use(void);

		std::string	name;
		GLint	glId;
		float	matrix[4][4];
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Matrix const &arg);
 
#endif // MATRIX_HPP

