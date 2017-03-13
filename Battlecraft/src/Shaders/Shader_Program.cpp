#include "Shader_Program.h"

namespace Shader 
{
	Shader_Program::Shader_Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	{

	}

	void Shader_Program::bind()
	{
		glUseProgram(m_programID);
	}

	void Shader_Program::unbind()
	{
		glUseProgram(0);
	}
}
