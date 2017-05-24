#include "Text_Shader.h"

Shader::Text_Shader::Text_Shader()
: Shader_Program("Text_Vertex", "Text_Fragment")
{
	getUniformLocations();
}

void Shader::Text_Shader::setProjMatrix(const Matrix4& matrix)
{
	loadMatrix4(m_locationProjMatrix, matrix);
}

void Shader::Text_Shader::setColorVector(const Vector3& vector)
{
	loadVector3(m_locationColor, vector);
}

void Shader::Text_Shader::getUniformLocations()
{
	m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
	m_locationColor = glGetUniformLocation(getID(), "textColor");
}
