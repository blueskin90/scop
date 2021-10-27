#include "Obj.hpp"

Obj	&Obj::operator=(Obj const &rhs)
{
	this->_path = rhs.getPath();
	return (*this);
	//assignation operator
}

Obj::Obj(void): _path("Path uninitialized"), _vao_id(0), _vbo_id(0), _ebo_id(0)
{
	//constructor 
}

Obj::Obj(std::string path): _path(path), _vao_id(0), _vbo_id(0), _ebo_id(0) 
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

const std::vector<Vector3int>&	Obj::getFaces(void) const
{
	return this->_faces;
}

int		Obj::genBuffers(void)
{
	for (unsigned long int i = 0; i < this->_vertices.size(); i++)
	{
		this->_vbo.push_back(this->_vertices[i].x);
		this->_vbo.push_back(this->_vertices[i].y);
		this->_vbo.push_back(this->_vertices[i].z);
	}

	for (unsigned long int i = 0; i < this->_faces.size(); i++)
	{
		this->_ebo.push_back(this->_faces[i].x);
		this->_ebo.push_back(this->_faces[i].y);
		this->_ebo.push_back(this->_faces[i].z);
	}

	glGenVertexArrays(1, &(this->_vao_id));
	glGenBuffers(1, &(this->_vbo_id));
	glGenBuffers(1, &(this->_ebo_id));

	glBindVertexArray(this->_vao_id);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * this->_vertices.size(), &(this->_vbo[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * this->_faces.size(), &(this->_ebo[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return (1);	
}

void	Obj::draw(void)
{
	glBindVertexArray(this->_vao_id);
	glDrawElements(GL_TRIANGLES, this->_faces.size() * 3, GL_UNSIGNED_INT, 0);
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
