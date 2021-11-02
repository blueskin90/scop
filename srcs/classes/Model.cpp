#include "Model.hpp"
 
Model	&Model::operator=(Model const &rhs)
{
	this->pos = rhs.pos;
	this->xaxis = rhs.xaxis;
	this->yaxis = rhs.yaxis;
	this->zaxis = rhs.zaxis;
	this->objToWorld = rhs.objToWorld
	return (*this);
}
 
Model::Model(): pos(0, 0, 0), xaxis(1, 0, 0), yaxis(0, 1, 0), zaxis(0, 0, -1) 
{
	this->objToWorld.init_identity();
	this->objToWorld.set_name("objToWorld");
}
 
 
Model::Model(Model const &src)
{
	this->pos = src.pos;
	this->xaxis = src.xaxis;
	this->yaxis = src.yaxis;
	this->zaxis = src.zaxis;
	this->objToWorld = src.objToWorld;
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

