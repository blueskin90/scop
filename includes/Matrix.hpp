#ifndef MATRIX_HPP
#define MATRIX_HPP
 
#include <iostream>
 
class Matrix
{
	public:
		Matrix();
		Matrix(Matrix const &src);
		virtual ~Matrix();
		Matrix&	operator=(Matrix const &rhs);
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Matrix const &arg);
 
#endif // MATRIX_HPP

