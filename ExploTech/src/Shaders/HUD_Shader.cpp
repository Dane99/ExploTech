#include "HUD_Shader.h"

Shader::HUD_Shader::HUD_Shader()
: Shader_Program("HUD_Vertex", "HUD_Fragment") 
{
	getUniformLocations();
}

// No uniform locations yet so this isn't needed, but the super class has it as a pure virtual function.
void Shader::HUD_Shader::getUniformLocations()
{
}
