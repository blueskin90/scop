#include "Vector.hpp"
 
Vector	&Vector::operator=(Vector const &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
	return (*this);
} 

Vector	Vector::operator+(Vector const &rhs) const
{
	return (Vector(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z));
}
 
Vector	&Vector::operator+=(Vector const &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return (*this);
}

Vector	Vector::operator-(Vector const &rhs) const
{
	return (Vector(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z));
}
 
Vector	&Vector::operator-=(Vector const &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return (*this);
}
 
Vector	Vector::operator*(float value) const
{
	return (Vector(this->x * value, this->y * value, this->z * value));
}
 
Vector	&Vector::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	return (*this);
}

Vector	Vector::operator/(float value) const
{
	return (Vector(this->x / value, this->y / value, this->z / value));
}
 
Vector	&Vector::operator/=(float value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	return (*this);
}

float	Vector::operator [](int i) const
{
	if (i == 0)
		return 	(this->x);
	else if (i == 1)
		return (this->y);
	else if (i == 2)
		return (this->z);
	else if (i == 3)
		return (this->w);
	throw std::out_of_range("max index is 3");

}
 
float	&Vector::operator [](int i)
{
	if (i == 0)
		return 	(this->x);
	else if (i == 1)
		return (this->y);
	else if (i == 2)
		return (this->z);
	else if (i == 3)
		return (this->w);
	throw std::out_of_range("max index is 3");
}

 
Vector::Vector(void): x(0), y(0), z(0), w(1)
{
}
 
Vector::Vector(float x, float y, float z): x(x), y(y), z(z), w(1)
{
}

Vector::Vector(float x, float y, float z, float w): x(x), y(y), z(z), w(w)
{
}

 
Vector::Vector(Vector const &src)
{
	this->x = src.x;
	this->y = src.y;
	this->z = src.z;
	this->w = src.w;
}
 
 
Vector::~Vector(void)
{
}
 
Vector	&Vector::normalize(void)
{
	float	magnitude;

	magnitude = this->len();
	if (magnitude == 0.0)
		return (*this);
	return (*this /= magnitude);	
}

float	Vector::len(void)
{
	return (std::sqrt(std::pow(this->x, 2) + std::pow(this->y, 2) + std::pow(this->z, 2)));
}

float	Vector::norm(void)
{
	return (this->len());
}

Vector	Vector::opposite(void)
{
	Vector	opp(-this->x, -this->y, -this->z);
	return (opp);
}
 
std::ostream&	operator<<(std::ostream &output, Vector const &rhs)
{
	output << "Vector : [" << rhs.x << "][" << rhs.y << "][" << rhs.z << "][" << rhs.w << "]";
	return (output);
//redirection operator
}

