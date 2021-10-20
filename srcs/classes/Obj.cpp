#include "Obj.hpp"
 
Obj	&Obj::operator=(Obj const &rhs)
{
	this->_path = rhs.getPath();
	return (*this);
//assignation operator
}
 
Obj::Obj(void): _path("No path was set")
{
//constructor 
}
  
Obj::Obj(std::string path): _path(path)
{
//constructor 
}
 
 
Obj::Obj(Obj const &src)
{
	this->_path = src.getPath();
}
 
 
Obj::~Obj(void)
{
//destructor
}

std::string Obj::getPath(void) const
{
	return(this->_path);
}

void	Obj::setPath(std::string path)
{
	this->_path = path;
}
 
 
std::ostream&	operator<<(std::ostream &output, Obj const &lhs)
{
	output << lhs.getPath();
	return (output);
}

