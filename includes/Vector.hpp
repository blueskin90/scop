#ifndef VECTOR_HPP
#define VECTOR_HPP
 
#include <iostream>
#include <cmath>
 
class Vector
{
	public:
		Vector(void);
		Vector(float x, float y, float z);
		Vector(float x, float y, float z, float w);
		Vector(Vector const &src);
		virtual ~Vector(void);

		Vector& normalize(void);

		float	len(void);
		float	norm(void);

		Vector&	operator=(Vector const &rhs);
		Vector	operator+(Vector const &rhs) const;
		Vector&	operator+=(Vector const &rhs);
		Vector	operator-(Vector const &rhs) const;
		Vector&	operator-=(Vector const &rhs);
		Vector	operator*(float value) const;
		Vector	&operator*=(float value);
		Vector	operator/(float value) const;
		Vector	&operator/=(float value);
		float operator [](int i) const;
		float & operator [](int i);

		float	x;
		float	y;
		float	z;
		float	w;
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Vector const &rhs);
 
#endif // VECTOR_HPP
