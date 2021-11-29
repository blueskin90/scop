#ifndef SHADER_HPP
#define SHADER_HPP
 
#include <iostream>
#include <string>

class Shader
{
	public:
		Shader();
		Shader(Shader const &src);
		virtual ~Shader();
		Shader&	operator=(Shader const &rhs);

		std::string getPath(void) const;
		std::string getContent(void) const;

		void setPath(std::string);
		void readFile(void);
	protected:
	private:
		std::string path;
		std::string content;
};
 
std::ostream&	operator<<(std::ostream &output,Shader const &arg);
 
#endif // SHADER_HPP

