#pragma once

class Application;
class Camera;

namespace Renderer
{
	class Master;
}

namespace State 
{
	class Game_State {
		public:
			Game_State();

			virtual void input			       () = 0;
			virtual void update			       (float dt) = 0;
			virtual void updateMouseInput      (double xpos, double ypos) = 0;
			virtual void updateMouseClickInput (bool left, bool right) = 0;
			virtual void updateKeyboardInput   (float dt) = 0;
			virtual void draw			       (Renderer::Master& renderer) = 0;

	};
}