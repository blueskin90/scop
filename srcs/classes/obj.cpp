#include "Obj.hpp"

Obj::Obj(std::string path): _path(path)
{
	std::cout << path << std::endl;
	if (path == "hello")
		throw WrongPathException();
}

const char* Obj::WrongPathException::what() const throw()
{
	return ("is an incorrect path");
}

Obj::~Obj(void)
{
	std::cout << "i was destroyed" << std::endl;
}


