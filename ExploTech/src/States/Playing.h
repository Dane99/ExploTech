#pragma once



#include "../Application.h"

namespace State 
{
	class Playing : public Game_State
	{
		public:
			Playing();

			void input () override;
			void update(float dt) override;
			void draw  (Renderer::Master& renderer) override;
			void updateMouseClickInput(bool left, bool right) override;
			void updateMouseInput(double xpos, double ypos) override;
			void updateKeyboardInput(float dt) override;

		private:
			HUD hud;
			WorldManager worldManager;
			static constexpr bool raycasting = true;
	};
}