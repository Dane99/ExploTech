#include "HUD_ShaderSimple.h"

Shader::HUD_ShaderSimple::HUD_ShaderSimple()
	: Shader_Program("HUD_Simple_Vertex", "HUD_Simple_Fragment")
{
	getUniformLocations();
}

void Shader::HUD_ShaderSimple::setProjMatrix(const Matrix4 & matrix)
{
	loadMatrix4(m_locationProjMatrix, matrix);
}

void Shader::HUD_ShaderSimple::getUniformLocations()
{
	m_locationProjMatrix = glGetUniformLocation(getID(), "projMatrix");
}
