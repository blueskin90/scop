#include "Shader.hpp"
 
Shader	&Shader::operator=(Shader const &rhs)
{
	this->path = rhs.getPath();
	this->content = rhs.getContent();
	return (*this);
}
 
Shader::Shader(): path("unitialized path"), content("")
{
//constructor 
}
 
 
Shader::Shader(Shader const &src)
{
	this->path = src.getPath();
	this->content = src.getContent();
}
 
 
Shader::~Shader()
{
//destructor
}

void	Shader::setPath(std::string path)
{
	this->path = path;
}

void	readFile(void)
{

}

std::string	Shader::getPath(void) const
{
	return (this->path);
}
 
std::string	Shader::getContent(void) const
{
	return (this->content);
}
 
 
std::ostream&	operator<<(std::ostream &output, Shader const &lhs)
{
	output << "path: " << lhs.getPath() << std::endl << "Content: " << lhs.getContent();
	return (output);
}

