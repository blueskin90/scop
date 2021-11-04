#include "Obj.hpp"

Obj	&Obj::operator=(Obj const &rhs)
{
	this->_path = rhs.getPath();
	return (*this);
	//assignation operator
}

Obj::Obj(void): _path("Path uninitialized"), _rotating(false) 
{
	//constructor 
}

Obj::Obj(std::string path): _path(path), _rotating(false) 
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

const char* Obj::WrongVerticeIndex::what() const throw()
{
	return ("An incorrect vertex indice was given");
}

void	Obj::addVertex(std::string line)
{
	std::regex re("v\\s+[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)\\s*[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)\\s*[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)\\s*");
	Vector v;

	if (!std::regex_match(line, re))
		throw BadlyFormatedLine();
	std::sscanf(&(line[0]), "v %f %f %f\n", &v.x, &v.y, &v.z);
	this->_vertices.push_back(v);
}

// fonction d'aide pour en dessous
bool	isOneOf(char c, const std::string compared)
{
	for (unsigned long int i = 0; i < compared.size(); i++)
		if (compared[i] == c)
			return true;
	return false;
}

std::vector<std::string> splitWhiteSpaces(const std::string &s, const std::string delims)
{
	std::string word;
	std::vector<std::string> splitted;
	
	for (unsigned int i = 0; i < s.size();)
	{
		if (isOneOf(s[i], delims) && i < s.size())
		{
			while (isOneOf(s[i], delims))
				i++;
		}
		else
		{
			word = "";
			while (isOneOf(s[i], delims) == false && i < s.size())
			{
				word.push_back(s[i]);
				i++;
			}
			splitted.push_back(word);
		}
	}
	return(splitted);
}

std::vector<int>	getIndexesFromSplittedString(std::vector<std::string> splitted)
{
	std::vector<int> array;

	for (unsigned long int i = 0; i < splitted.size(); i++)
		array.push_back(std::stoi(splitted[i]));
	return (array);
}

void	Obj::addFace(std::string line)
{
	std::regex re("^f(\\s+[0-9]+){3,}");

	if (!std::regex_match(line, re))
		throw BadlyFormatedLine();

	line.erase(0, 1);

	std::vector<std::string>splitted = splitWhiteSpaces(line, " \t\r\v\f");
	std::vector<int> faceIndex = getIndexesFromSplittedString(splitted);
	for (unsigned long int i = 0; i < faceIndex.size(); i++)
		if (faceIndex[i] < 0 || (unsigned long int)faceIndex[i] > this->_vertices.size())
			throw WrongVerticeIndex();


	if (faceIndex.size() == 3)
	{
		Vector3int v(faceIndex[0], faceIndex[1], faceIndex[2]);
		this->_faces.push_back(v);
	}
	else
		std::cout << "Je ne gere pas encore les faces a plus de 3 index" << std::endl;
/*
	std::cout << "face : ";
	for (unsigned long int i = 0; i < faceIndex.size(); i++)
		std::cout << splitted[i] << "\n";
	std::cout << std::endl;
*/	
}

void	Obj::center(void)
{
	Vector	min = this->_vertices[0];
	Vector	max = this->_vertices[0];
	Vector center;

	for (unsigned int i = 1; i < this->_vertices.size(); i++)
	{
		for (int j = 0; i < 3; i++)
			min[j] = (this->_vertices[i][j] < min[j]) ? this->_vertices[i][j] : min[j];
		for (int j = 0; i < 3; i++)
			max[j] = (this->_vertices[i][j] > max[j]) ? this->_vertices[i][j] : max[j];
	}
	center = (max - min) / 2.0;
//	std::cout << "center = " << center << std::endl;
	for (unsigned int i = 0; i < this->_vertices.size(); i++)
	{
		this->_vertices[i] -= center;
	}	
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
	this->center();
}

void	Obj::setPath(std::string path)
{
	this->_path = path;
}

const std::vector<Vector>&	Obj::getVertices(void) const
{
	return this->_vertices;
}

const std::vector<Vector3int>&	Obj::getFaces(void) const
{
	return this->_faces;
}
void		Obj::genBuffers(void)
{
	this->_model.genBuffers(this->_vertices, this->_faces);
}

void	Obj::draw(void)
{
	this->_model.draw();
}

void	Obj::toggleRotation(void)
{
	this->_rotating ^= true;
}

void	Obj::update(void)
{
	if (this->_rotating == true)
		this->_model.pitch(1);
	this->_model.objToWorld.use();
}

void	Obj::bindToProgram(GLuint program)
{
	this->_model.bindToProgram(program);
}

std::ostream&	operator<<(std::ostream &output, Obj const &lhs)
{
	output << lhs.getPath() << std::endl;
	const std::vector<Vector> &v = lhs.getVertices();

	for (unsigned long int i = 0; i < lhs.getVertices().size(); i++)
		std::cout << v[i] << std::endl;

	const std::vector<Vector3int> &v2 = lhs.getFaces();

	for (unsigned long int i = 0; i < lhs.getFaces().size(); i++)
		std::cout << v2[i] << std::endl;

	return (output);
}
