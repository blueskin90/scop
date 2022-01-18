#ifndef SHADER_HPP
#define SHADER_HPP
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define GL_SILENCE_DEPRECATION

#include "glincludes.hpp"


#ifdef __linux__

#define VERTEX_SHADER_PATH "/mnt/nfs/homes/toliver/sgoinfre/scop/srcs/shaders/vertex.glsl"
#define GEOMETRY_SHADER_PATH "/mnt/nfs/homes/toliver/sgoinfre/scop/srcs/shaders/geometry.glsl"
#define FRAGMENT_SHADER_PATH "/mnt/nfs/homes/toliver/sgoinfre/scop/srcs/shaders/fragment.glsl"

#endif

#ifdef __APPLE__

#define VERTEX_SHADER_PATH "/sgoinfre/goinfre/Perso/toliver/scop/srcs/shaders/vertex.glsl"
#define GEOMETRY_SHADER_PATH "/sgoinfre/goinfre/Perso/toliver/scop/srcs/shaders/geometry.glsl"
#define FRAGMENT_SHADER_PATH "/sgoinfre/goinfre/Perso/toliver/scop/srcs/shaders/fragment.glsl"

#endif 



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
