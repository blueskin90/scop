#ifndef SHADER_HPP
#define SHADER_HPP
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

class Shader
{
	public:
		Shader();
		Shader(std::string const path);
		Shader(Shader const &src);
		virtual ~Shader();
		Shader&	operator=(Shader const &rhs);

		std::string getPath(void) const;
		std::string getContent(void) const;

		void setPath(std::string);
        void compile(GLenum shaderType);
		void readFile(void);
        GLuint  id;
	protected:
	private:
		std::string path;
		std::string content;
};
 
std::ostream&	operator<<(std::ostream &output,Shader const &arg);
 
#endif // SHADER_HPP

