#pragma once

#include "Game_State.h"

#include "../Model.h"
#include "../Shaders/Simple_Shader.h"
#include "../Texture/Texture_Atlas.h"

#include "../World/Chunk/Chunk.h"
#include "../Temp/Quad.h"

namespace State 
{
	class Playing : public Game_State
	{
		public:
			Playing(Application &application);

			void input (Camera& camera) override;
			void update(Camera& camera, float dt) override;
			void draw  (Renderer::Master& renderer) override;
			void updateMouseInput(Camera& camera, double xpos, double ypos) override;
			void updateKeyboardInput(Camera& camera, float dt) override;

		private:
			Shader::Simple_Shader m_shader;
			//Texture::Atlas m_texture;

			Quad m_quad;
			Chunk chunk;
	};


}