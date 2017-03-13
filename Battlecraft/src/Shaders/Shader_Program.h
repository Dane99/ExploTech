#pragma once
#include "GL/glew.h"
#include <string>

namespace Shader 
{
	class Shader_Program
	{
		public:
			Shader_Program(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

			void bind();
			void unbind();

		private:
			GLuint m_programID;
			GLuint m_vertexShaderID;
			GLuint m_fragmentShaderID;
	};
}