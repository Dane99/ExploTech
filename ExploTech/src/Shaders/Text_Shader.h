#pragma once

#include "Shader_Program.h"

namespace Shader
{
	class Text_Shader : public Shader_Program
	{
	public:
		Text_Shader();

		void setProjMatrix(const Matrix4& matrix);

	private:
		void getUniformLocations() override;

		GLuint m_locationProjMatrix = 0;
	};
}