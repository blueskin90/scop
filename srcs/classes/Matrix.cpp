#include "Matrix.hpp"

float	degToRad(float angle)
{
	return (angle * M_PI / 180.0);
}

float	radToDeg(float angle)
{
	return (angle * 180 / M_PI);
}
 
Matrix	&Matrix::operator=(Matrix const &rhs)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
			this->matrix[y][x] = rhs.matrix[y][x];
	}
	return (*this);
}
 
Matrix::Matrix(): name("unnamed"), glId(0)
{
	this->init_identity();
}
 
 
Matrix::Matrix(Matrix const &src)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
			this->matrix[y][x] = src.matrix[y][x];
	}
}
 
Matrix::~Matrix()
{
//destructor
}

Matrix	Matrix::operator*(Matrix const &rhs) const
{
	Matrix	m;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			m.matrix[y][x] = this->matrix[y][0] * rhs.matrix[0][x]
				+ this->matrix[y][1] * rhs.matrix[1][x]
				+ this->matrix[y][2] * rhs.matrix[2][x]
				+ this->matrix[y][3] * rhs.matrix[3][x];
		}
	}
	return (m);
}

Matrix&	Matrix::operator*=(Matrix const &rhs)
{
	*this = (*this) * rhs;
	return (*this);
}

Vector	Matrix::operator*(Vector const &rhs) const
{
	Vector		c;

	c.x = this->matrix[0][0] * rhs.x + this->matrix[0][1] * rhs.y + this->matrix[0][2] * rhs.z
		+ this->matrix[0][3] * rhs.w;
	c.y = this->matrix[1][0] * rhs.x + this->matrix[1][1] * rhs.y + this->matrix[1][2] * rhs.z
		+ this->matrix[1][3] * rhs.w;
	c.z = this->matrix[2][0] * rhs.x + this->matrix[2][1] * rhs.y + this->matrix[2][2] * rhs.z
		+ this->matrix[2][3] * rhs.w;
	c.w = this->matrix[3][0] * rhs.x + this->matrix[3][1] * rhs.y + this->matrix[3][2] * rhs.z
		+ this->matrix[3][3] * rhs.w;
	return (c);	
	// a l'air de marcher
}

void	Matrix::set_name(std::string name)
{
	this->name = name;
}
 
void	Matrix::init_perspective(void)
{
    float fov = 90.0;
    float near =0;
    float far = 100;

    fov = degToRad(fov);
    float aspect = 600.0/800;
    float xscale = 1 / tanf(fov * 0.5);
    float yscale = xscale / aspect;
    this->init_identity();

    this->matrix[0][0] = xscale;
    this->matrix[1][1] = yscale;
    this->matrix[2][2] = -(far + near) / (far - near);
    this->matrix[2][3] = -1;
    this->matrix[3][2] = -2 * far * near / (far - near);
    this->matrix[3][3] = 0;
}

 
void	Matrix::init_identity(void)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
			this->matrix[y][x] = 0;
	}
	for (int i = 0; i < 4; i++)
		this->matrix[i][i] = 1;
}

void	Matrix::init_translation(Vector t)
{
	this->init_identity();
	for (int i = 0; i < 3; i++)
		this->matrix[3][i] = t[i];
}

void	Matrix::init_rotation(Vector axis, float angle)
{
	float	sin;
	float	cos;

	angle = degToRad(angle);
	sin = sinf(angle);
	cos = cosf(angle);
	this->init_identity();
	this->matrix[0][0] = cos + axis.x * axis.x * (1.0 - cos);
	this->matrix[0][1] = axis.x * axis.y * (1.0 - cos) + axis.z * sin;
	this->matrix[0][2] = axis.x * axis.z * (1.0 - cos) - axis.y * sin;
	this->matrix[1][0] = axis.x * axis.y * (1.0 - cos) - axis.z * sin;
	this->matrix[1][1] = cos + axis.y * axis.y * (1.0 - cos);
	this->matrix[1][2] = axis.y * axis.z * (1.0 - cos) + axis.x * sin;
	this->matrix[2][0] = axis.x * axis.z * (1.0 - cos) + axis.y * sin;
	this->matrix[2][1] = axis.y * axis.z * (1.0 - cos) - axis.x * sin;
	this->matrix[2][2] = cos + axis.z * axis.z * (1.0 - cos);
}

void	Matrix::init_scale(float scale)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
			this->matrix[y][x] = 0;
	}
	for (int i = 0; i < 3; i++)
		this->matrix[i][i] = scale;
	this->matrix[3][3] = 1;
}

void	Matrix::bind_to_program(GLuint program) // penser a throw un truc si ca fail
{
	this->glId = glGetUniformLocation(program, this->name.c_str());
	std::cout << this->name.c_str() << std::endl;
	glUniformMatrix4fv(this->glId, 1, GL_FALSE, (float*)&this->matrix[0]);
	std::cout << "Matrix rhs.nd id is : " << this->glId << std::endl;
}

void	Matrix::use(void)
{
	glUniformMatrix4fv(this->glId, 1, GL_FALSE, (float*)this->matrix);
}
 
std::ostream&	operator<<(std::ostream &output, Matrix const &lhs)
{
	output << std::setprecision(2) << "[" << lhs.matrix[0][0] << "][" << lhs.matrix[0][1] << "][" << lhs.matrix[0][2] << "][" << lhs.matrix[0][3] << "]" << std::endl;
	output << std::setprecision(2) << "[" << lhs.matrix[1][0] << "][" << lhs.matrix[1][1] << "][" << lhs.matrix[1][2] << "][" << lhs.matrix[1][3] << "]" << std::endl;
	output << std::setprecision(2) << "[" << lhs.matrix[2][0] << "][" << lhs.matrix[2][1] << "][" << lhs.matrix[2][2] << "][" << lhs.matrix[2][3] << "]" << std::endl;
	output << std::setprecision(2) << "[" << lhs.matrix[3][0] << "][" << lhs.matrix[3][1] << "][" << lhs.matrix[3][2] << "][" << lhs.matrix[3][3] << "]" << std::endl;
	return (output);
}

