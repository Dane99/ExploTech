#include "Shader_Loader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Shader
{
	GLuint compileShader(const GLchar* source, GLenum type)
	{
		auto id = glCreateShader(type);

		glShaderSource(id, 1, &source, nullptr);
		glCompileShader(id);

		GLint isSuccess;
		GLchar infoLog[512];

		glGetShaderiv(id, GL_COMPILE_STATUS, &isSuccess);

		if (!isSuccess) 
		{
			glGetShaderInfoLog(id, 512, nullptr, infoLog);
			throw std::runtime_error("Error compiling shader: " + std::string(infoLog));
		}

		return id;
	}

	std::string getSource(const std::string& sourceFile) {
		std::ifstream inFile("Data/Shaders/" + sourceFile + ".glsl");
		std::string source;
		std::stringstream stringStream;


		if (!inFile.is_open()) 
		{
			throw std::runtime_error{ "Could not open file: " + sourceFile };
		}

		stringStream << inFile.rdbuf();
		source = stringStream.str();

		return source;
	}

	GLuint LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{
		auto vertexSource   = getSource(vertexShaderFile);
		auto fragmentSource = getSource(fragmentShaderFile);

	}
}