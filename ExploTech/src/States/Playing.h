#pragma once

#include "Game_State.h"

#include "../Model.h"
#include "../Shaders/Simple_Shader.h"
#include "../Texture/Texture_Atlas.h"

#include "../World/Chunk/Chunk.h"
#include "../Temp/Quad.h"

#include "../World/Chunk/World_Manager.h"

#include "../HUD/HUD.h"
#include "../Text/Text_Manager.h"

namespace State 
{
	class Playing : public Game_State
	{
		public:
			Playing(Application &application);

			void input () override;
			void update(float dt) override;
			void draw  (Renderer::Master& renderer) override;
			void updateMouseClickInput(bool left, bool right) override;
			void updateMouseInput(double xpos, double ypos) override;
			void updateKeyboardInput(float dt) override;

		private:
			Shader::Simple_Shader m_shader;
			//Texture::Atlas m_texture;

			Quad m_quad;
			//Chunk chunk;
			World_Manager worldManager;

			HUD hud;

			Text_Manager textManager;


			static constexpr bool raycasting = false;
	};


}