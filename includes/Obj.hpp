#ifndef OBJ_HPP
#define OBJ_HPP
 
#include <iostream>
#include <Vector.hpp>
 
class Obj
{
	public:
		Obj(void);
		Obj(std::string path);
		Obj(Obj const &src);
		virtual ~Obj(void);
		Obj&	operator=(Obj const &rhs);

		std::string getPath(void) const;
		void	setPath(std::string path);
	protected:
	private:
		std::string _path;
		std::vector<Vector> _vertices;
};
 
std::ostream&	operator<<(std::ostream &output,Obj const &arg);
 
#endif // OBJ_HPP

