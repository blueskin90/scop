#include "Vector3int.hpp"
 
Vector3int	&Vector3int::operator=(Vector3int const &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return (*this);
} 

Vector3int	Vector3int::operator+(Vector3int const &rhs) const
{
	return (Vector3int(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z));
}
 
Vector3int	&Vector3int::operator+=(Vector3int const &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return (*this);
}

Vector3int	Vector3int::operator-(Vector3int const &rhs) const
{
	return (Vector3int(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z));
}
 
Vector3int	&Vector3int::operator-=(Vector3int const &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return (*this);
}
 
Vector3int	Vector3int::operator*(int value) const
{
	return (Vector3int(this->x * value, this->y * value, this->z * value));
}
 
Vector3int	&Vector3int::operator*=(int value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return (*this);
}

Vector3int	Vector3int::operator/(int value) const
{
	return (Vector3int(this->x / value, this->y / value, this->z / value));
}
 
Vector3int	&Vector3int::operator/=(int value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return (*this);
}

int	Vector3int::operator [](int i) const
{
	if (i == 0)
		return 	(this->x);
	else if (i == 1)
		return (this->y);
	else if (i == 2)
		return (this->z);
	throw std::out_of_range("max index is 2");

}
 
int	&Vector3int::operator [](int i)
{
	if (i == 0)
		return 	(this->x);
	else if (i == 1)
		return (this->y);
	else if (i == 2)
		return (this->z);
	throw std::out_of_range("max index is 2");
}

 
Vector3int::Vector3int(void): x(0), y(0), z(0)
{
}
 
Vector3int::Vector3int(int x, int y, int z): x(x), y(y), z(z)
{
}

Vector3int::Vector3int(Vector3int const &src)
{
	this->x = src.x;
	this->y = src.y;
	this->z = src.z;
}
 
 
Vector3int::~Vector3int(void)
{
}
 
Vector3int	&Vector3int::normalize(void)
{
	int	magnitude;

	magnitude = this->len();
	if (magnitude == 0.0)
		return (*this);
	return (*this /= magnitude);	
}

int	Vector3int::len(void)
{
	return (std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2)));
}

int	Vector3int::norm(void)
{
	return (this->len());
}
 
std::ostream&	operator<<(std::ostream &output, Vector3int const &rhs)
{
	output << "Vector3int : [" << rhs.x << "][" << rhs.y << "][" << rhs.z << "]";
	return (output);
//redirection operator
}

