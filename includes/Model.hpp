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
	protected:
	private:
};
 
std::ostream&	operator<<(std::ostream &output,Model const &arg);
 
#endif // MODEL_HPP

