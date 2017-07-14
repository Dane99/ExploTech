#pragma once

#include "../HUD/HUD.h"
#include "../Shaders/HUD_Shader.h"
#include "../Shaders/HUD_ShaderSimple.h"

#include <SFML/System/Clock.hpp>

namespace Renderer
{
	class HUD_Renderer
	{
	public:

		void addToHudRenderList(HUD& hud);

		void update();

	private:

		Shader::HUD_Shader m_shader;
		Shader::HUD_ShaderSimple m_shaderSimple;
		HUD* m_hud;
		sf::Clock m_clock;
	};
}