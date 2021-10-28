#include "Model.hpp"
 
Model	&Model::operator=(Model const &rhs)
{
//assignation operator
	(void)rhs;
	return (*this);
}
 
Model::Model()
{
//constructor 
}
 
 
Model::Model(Model const &src)
{
	(void)src;
//copy constructor
}
 
 
Model::~Model()
{
//destructor
}
 
 
std::ostream&	operator<<(std::ostream &output, Model const &lhs)
{
//redirection operator
	(void)lhs;
	return (output);
}

