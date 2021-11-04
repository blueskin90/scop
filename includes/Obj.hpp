#ifndef OBJ_HPP
#define OBJ_HPP

# define GL_SILENCE_DEPRECATION

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <string>
#include <cstdio>
#include "Vector.hpp"
#include "Vector3int.hpp"
#include "Model.hpp"

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h> // GLFW helper library

 
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
		const std::vector<Vector3int>&	getFaces(void) const;
		void	parseFile(void);

		void	genBuffers(void);
		void	draw(void);

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
		class WrongVerticeIndex: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};

	private:
		Model					_model;
		std::string 			_path;
		std::vector<Vector> 	_vertices;
		std::vector<Vector3int> _faces;

		void	center(void);
};
 
std::ostream&	operator<<(std::ostream &output,Obj const &arg);
 
#endif // OBJ_HPP

