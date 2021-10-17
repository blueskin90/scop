#ifndef OBJ_HPP
#define OBJ_HPP

#include <iostream>


class Obj {
	public:
		Obj(std::string path);
		~Obj(void);


	class WrongPathException : public std::exception {
		public:
			virtual const char* what() const throw();
	};

	private:
		std::string	_path;
};

#endif /* OBJ_HPP */
