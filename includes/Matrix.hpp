#ifndef MATRIX_HPP
#define MATRIX_HPP
 
#include <iostream>
#include "Vector.hpp"
#include <iomanip>

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

		void	set_name(std::string name);


		std::string	name;
		float	matrix[4][4];
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Matrix const &arg);
 
#endif // MATRIX_HPP

