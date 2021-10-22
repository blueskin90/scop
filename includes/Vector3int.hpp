#ifndef VECTOR3INT_HPP
#define VECTOR3INT_HPP
 
#include <iostream>
#include <cmath>
 
class Vector3int
{
	public:
		Vector3int(void);
		Vector3int(int x, int y, int z);
		Vector3int(Vector3int const &src);
		virtual ~Vector3int(void);

		Vector3int& normalize(void);

		int	len(void);
		int	norm(void);

		Vector3int&	operator=(Vector3int const &rhs);
		Vector3int	operator+(Vector3int const &rhs) const;
		Vector3int&	operator+=(Vector3int const &rhs);
		Vector3int	operator-(Vector3int const &rhs) const;
		Vector3int&	operator-=(Vector3int const &rhs);
		Vector3int	operator*(int value) const;
		Vector3int	&operator*=(int value);
		Vector3int	operator/(int value) const;
		Vector3int	&operator/=(int value);
		int operator [](int i) const;
		int & operator [](int i);

		int	x;
		int	y;
		int	z;
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Vector3int const &rhs);
 
#endif // VECTOR3INT_HPP
