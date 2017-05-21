#pragma once

#include "Shader_Program.h"

namespace Shader
{
	class HUD_Shader : public Shader_Program
	{
	public:
		HUD_Shader();

		void setTime(float time);

	private:
		void getUniformLocations() override;

		GLuint m_locationTime = 0;
	};
}