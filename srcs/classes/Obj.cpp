#include "Obj.hpp"

Obj	&Obj::operator=(Obj const &rhs)
{
	this->_path = rhs.getPath();
	return (*this);
	//assignation operator
}

Obj::Obj(void): _path("Path uninitialized")
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

const char* Obj::BadlyFormatedLine::what() const throw()
{
	return ("a line was badly formatted.");
}

const char* Obj::FileError::what() const throw()
{
	return ("Something went wrong when reading the file");
}

void	Obj::addVertex(std::string line)
{
	std::regex re("v\\s*[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)\\s*[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)\\s*[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)\\s*");
	Vector v;

	if (!std::regex_match(line, re))
		throw BadlyFormatedLine();
	std::sscanf(&(line[0]), "v %f %f %f\n", &v.x, &v.y, &v.z);
	this->_vertices.push_back(v);
}

void	Obj::addFace(std::string line)
{
	std::cout << "add face: " << line << std::endl;
}

void	Obj::parseFile(void)
{
	std::ifstream file;

	file.open(this->_path);
	if (!file)
		throw FileError();
	for (std::string line; getline(file, line); )
	{
		if (line[0] == 'o')
			std::cerr << "Not handling having different object in obj file: " << line << std::endl;
		else if (line.rfind("mtllib", 0) == 0)
			std::cerr << "Not handling mtllib in obj file : " << line << std::endl;
		else if (line.rfind("usemtl", 0) == 0)
			std::cerr << "Not handling usemtl in obj file : " << line << std::endl;
		else if (line[0] == 's')
			std::cerr << "not handling smooth shading: " << line << std::endl;
		else if (line[0] == 'v')
			this->addVertex(line);
		else if (line[0] == 'f')
			this->addFace(line);
		else if (line[0] != '#')
			std::cout << "unknown line type : " << line << std::endl;
	}
	file.close();
}

void	Obj::setPath(std::string path)
{
	this->_path = path;
}

const std::vector<Vector>&	Obj::getVertices(void) const
{
	return this->_vertices;
}

std::ostream&	operator<<(std::ostream &output, Obj const &lhs)
{
	output << lhs.getPath() << std::endl;
	const std::vector<Vector> &v = lhs.getVertices();

	for (unsigned long int i = 0; i < lhs.getVertices().size(); i++)
		std::cout << v[i] << std::endl;
	return (output);
}
