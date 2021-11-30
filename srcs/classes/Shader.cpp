#include "Shader.hpp"

Shader	&Shader::operator=(Shader const &rhs)
{
    this->path = rhs.getPath();
    this->content = rhs.getContent();
    return (*this);
}

Shader::Shader(): path("unitialized path"), content("")
{
    //constructor 
}

Shader::Shader(std::string const npath): path(npath), content("")
{

}

Shader::Shader(Shader const &src)
{
    this->path = src.getPath();
    this->content = src.getContent();
}


Shader::~Shader()
{
    glDeleteShader(this->id);
    //destructor
}

void	Shader::setPath(std::string path)
{
    this->path = path;
}

void    Shader::compile(GLenum shaderType)
{
    char    *content;

    this->readFile();
    content = (char*)this->content.c_str();
    this->id = glCreateShader(shaderType);
    glShaderSource(this->id, 1, &content, NULL);
    glCompileShader(this->id);

    GLint isCompiled = 0;
    glGetShaderiv(this->id, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &maxLength);
        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(this->id, maxLength, &maxLength, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        std::string str(errorLog.begin(), errorLog.end());
        std::cout << "There was a problem when compiling a Shader: " << this->path << "\n" << str << std::endl;
        // Exit with failure.
        glDeleteShader(this->id); // Don't leak the shader.
        return;
    }
}

void	Shader::readFile(void)
{
    std::ifstream f(this->path);
    std::string str;

    if(f) 
    {
        std::ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    //std::cout << str << std::endl;
    this->content = str;
}

std::string	Shader::getPath(void) const
{
    return (this->path);
}

std::string	Shader::getContent(void) const
{
    return (this->content);
}


std::ostream&	operator<<(std::ostream &output, Shader const &lhs)
{
    output << "path: " << lhs.getPath() << std::endl << "Content: " << lhs.getContent();
    return (output);
}

