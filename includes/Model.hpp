#ifndef MODEL_HPP
#define MODEL_HPP
 
#include <iostream>
#include <vector>

#include "Vector.hpp"
#include "Vector3int.hpp"
#include "Matrix.hpp"

#include "glincludes.hpp"

 
class Model
{
	public:
		Model();
		Model(Model const &src);
		virtual ~Model();
		Model&	operator=(Model const &rhs);

		void	bindToProgram(GLuint program);
		void	genBuffers(std::vector<Vector> &vertices, std::vector<Vector3int> &faces);
		void	draw(void);

		void	move(Vector	dir);
		void	rotate(Vector axis, float angle);
        void    roll(float angle);
        void    pitch(float angle);
        void    yawn(float angle);

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

