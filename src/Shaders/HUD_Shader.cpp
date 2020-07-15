#include "HUD_Shader.h"

Shader::HUD_Shader::HUD_Shader()
: Shader_Program("HUD_Vertex", "HUD_Fragment") 
{
	getUniformLocations();
}

void Shader::HUD_Shader::setTime(float time)
{
	loadFloat(m_locationTime, time);
}

void Shader::HUD_Shader::setProjMatrix(const Matrix4& matrix)
{
	loadMatrix4(m_locationProjMatrix, matrix);
}

void Shader::HUD_Shader::getUniformLocations()
{
	m_locationTime = glGetUniformLocation(getID(), "time");
	m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
}
