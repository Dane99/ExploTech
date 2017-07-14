#pragma once

#include "Shader_Program.h"

namespace Shader
{
	class HUD_ShaderSimple : public Shader_Program
	{
	public:
		HUD_ShaderSimple();

		void setProjMatrix(const Matrix4& matrix);

	private:
		void getUniformLocations() override;

		GLuint m_locationProjMatrix = 0;
	};
}