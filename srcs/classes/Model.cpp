#include "Model.hpp"
 
Model	&Model::operator=(Model const &rhs)
{
	this->pos = rhs.pos;
	this->xaxis = rhs.xaxis;
	this->yaxis = rhs.yaxis;
	this->zaxis = rhs.zaxis;
	this->objToWorld = rhs.objToWorld;
	return (*this);
}
 
Model::Model(): pos(0, 0, 0), xaxis(1, 0, 0), yaxis(0, 1, 0), zaxis(0, 0, -1) 
{
	this->objToWorld.init_identity();
	this->objToWorld.set_name("objToWorld");
}
 
 
Model::Model(Model const &src)
{
	this->pos = src.pos;
	this->xaxis = src.xaxis;
	this->yaxis = src.yaxis;
	this->zaxis = src.zaxis;
	this->objToWorld = src.objToWorld;
}

Model::~Model()
{
//destructor
}

const char* Model::BufferCreationFailed::what() const throw()
{
	return ("Something went wrong when creating buffer objects");
}
 
void	Model::genBuffers(std::vector<Vector> &vertices, std::vector<Vector3int> &faces)
{
	for (unsigned long int i = 0; i < vertices.size(); i++)
	{
		this->_vbo.push_back(vertices[i].x);
		this->_vbo.push_back(vertices[i].y);
		this->_vbo.push_back(vertices[i].z);
	}

	for (unsigned long int i = 0; i < faces.size(); i++)
	{
		this->_ebo.push_back((unsigned int)faces[i].x - 1);
		this->_ebo.push_back((unsigned int)faces[i].y - 1);
		this->_ebo.push_back((unsigned int)faces[i].z - 1);
	}

	glGenVertexArrays(1, &(this->_vaoId));
	glGenBuffers(1, &(this->_vboId));
	glGenBuffers(1, &(this->_eboId));

	if (this->_vaoId < 0 || this->_vboId < 0 || this->_eboId < 0)
		throw BufferCreationFailed(); 
	glBindVertexArray(this->_vaoId);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * vertices.size(), &(this->_vbo[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * faces.size(), &(this->_ebo[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::cout << this->_vbo.size() << std::endl;
	std::cout << this->_ebo.size() << std::endl;
	std::cout << this->_vaoId << std::endl;
	std::cout << this->_vboId << std::endl;
	std::cout << this->_eboId << std::endl;
}
 
void	Model::draw(void)
{
	glBindVertexArray(this->_vaoId);
	glDrawElements(GL_TRIANGLES, this->_ebo.size(), GL_UNSIGNED_INT, 0);
}

 
void	Model::move(Vector dir)
{
	this->pos += dir;

    Matrix tra;
    tra.init_translation(dir);
	this->objToWorld = this->objToWorld * tra;
}

void    Model::roll(float angle)
{
    this->rotate(this->zaxis, angle);
}
void    Model::pitch(float angle)
{
    this->rotate(this->yaxis, angle);
}
void    Model::yawn(float angle)
{
    this->rotate(this->xaxis, angle);
}

void	Model::rotate(Vector axis, float angle)
{
    Matrix rot;

    rot.init_rotation(axis, angle);
	this->objToWorld = this->objToWorld * rot; // check plus tard si ca marche bien
    this->xaxis = rot * this->xaxis; // les axes ne changent pas
    this->yaxis = rot * this->yaxis;
    this->zaxis = rot * this->zaxis;
}

void	Model::bindToProgram(GLuint program)
{
	this->objToWorld.bind_to_program(program);
}

 
std::ostream&	operator<<(std::ostream &output, Model const &lhs)
{
//redirection operator
	(void)lhs;
	return (output);
}

