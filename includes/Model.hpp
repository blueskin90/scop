#ifndef MODEL_HPP
#define MODEL_HPP
 
#include <iostream>
 
class Model
{
	public:
		Model();
		Model(Model const &src);
		virtual ~Model();
		Model&	operator=(Model const &rhs);

		Vector						pos;

		Vector						xaxis;
		Vector						yaxis;
		Vector						zaxis;

		Matrix						objToWorld;
	protected:
	private:
		std::vector<float>			_vao;
		std::vector<float>			_vbo;
		std::vector<unsigned int>	_ebo;
		GLuint						_vaoId;
		GLuint						_vboId;
		GLuint						_eboId;
};
 
//std::ostream&	operator<<(std::ostream &output,Model const &arg);
 
#endif // MODEL_HPP

