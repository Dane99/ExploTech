#pragma once

#include "Shader_Program.h"

namespace Shader
{
	class HUD_Shader : public Shader_Program
	{
	public:
		HUD_Shader();


	private:
		void getUniformLocations() override;
	};
}