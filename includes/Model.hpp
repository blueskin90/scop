#ifndef MODEL_HPP
#define MODEL_HPP
 
#include <iostream>
#include <vector>

#include "Vector.hpp"
#include "Vector3int.hpp"
#include "Matrix.hpp"

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

 
class Model
{
	public:
		Model();
		Model(Model const &src);
		virtual ~Model();
		Model&	operator=(Model const &rhs);

		void	genBuffers(std::vector<Vector> &vertices, std::vector<Vector3int> &faces);
		void	draw(void);

		Vector						pos;

		Vector						xaxis;
		Vector						yaxis;
		Vector						zaxis;

		Matrix						objToWorld;

	protected:
		class BufferCreationFailed: public std::exception
		{
			public:
				virtual const char* what() const throw();
		};
	private:
		std::vector<float>			_vbo;
		std::vector<unsigned int>	_ebo;
		GLuint						_vaoId;
		GLuint						_vboId;
		GLuint						_eboId;
};
 
//std::ostream&	operator<<(std::ostream &output,Model const &arg);
 
#endif // MODEL_HPP

