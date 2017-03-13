#pragma once

#include "GL/glew.h"
#include <string>

namespace Shader
{
	GLuint LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

}