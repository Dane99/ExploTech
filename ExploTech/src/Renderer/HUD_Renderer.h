#pragma once

#include "../HUD/HUD.h"
#include "../Shaders/HUD_Shader.h"

namespace Renderer
{
	class HUD_Renderer
	{
	public:

		void addToHudRenderList(HUD& hud);

		void update();

	private:

		Shader::HUD_Shader shader;
		HUD* hud;
	};
}