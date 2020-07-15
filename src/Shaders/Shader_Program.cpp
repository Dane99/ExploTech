#include "Shader_Program.h"

#include "Shader_Loader.h"

namespace Shader 
{
	Shader_Program::Shader_Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
		: m_programID(loadShader(vertexShaderFile, fragmentShaderFile))
	{
	}

	Shader_Program::~Shader_Program()
	{
		glDeleteProgram(m_programID);
	}

	void Shader_Program::bind()
	{
		glUseProgram(m_programID);
	}

	void Shader_Program::unbind()
	{
		glUseProgram(0);
	}

	GLuint Shader_Program::getID() const
	{
		return m_programID;
	}

	void Shader_Program::loadFloat(GLuint location, float value)
	{
		glUniform1f(location, value);
	}

	void Shader_Program::loadVector2(GLuint location, const Vector2& vector)
	{
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader_Program::loadVector3(GLuint location, const Vector3& vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader_Program::loadVector4(GLuint location, const Vector4& vector)
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader_Program::loadMatrix4(GLuint location, const Matrix4& matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
