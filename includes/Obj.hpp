#ifndef OBJ_HPP
#define OBJ_HPP
 
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <cstdio>
#include "Vector.hpp"
#include "Vector3int.hpp"

 
class Obj
{
	public:
		Obj(void);
		Obj(std::string path);
		Obj(Obj const &src);
		virtual ~Obj(void);
		Obj&	operator=(Obj const &rhs);

		void	addVertex(std::string);
		void	addFace(std::string);

		std::string getPath(void) const;
		void	setPath(std::string path);
		const std::vector<Vector>&	getVertices(void) const;
		void	parseFile(void);
	protected:
		class BadlyFormatedLine: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
		class FileError: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	private:
		std::string _path;
		std::vector<Vector> _vertices;
		std::vector<Vector3int> _faces;
};
 
std::ostream&	operator<<(std::ostream &output,Obj const &arg);
 
#endif // OBJ_HPP

