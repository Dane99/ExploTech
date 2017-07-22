#pragma once

#include <stack>
#include <memory>
#include "States/Game_State.h"

#include "Renderer/Master_Renderer.h"

#include "Entity.h"
#include "Camera.h"


//#include "Util\Singleton.h"

class Application{
	public:

		static Application& get();

		void runMainGameLoop();

		void pushState(std::unique_ptr<State::Game_State> state);
		void popState();

		Camera& getCamera();

		State::Game_State* getCurrentGameStatePtr();

		

	//	static State::Game_State* getGameState();

	private:
		Application();
		~Application();

		std::stack<std::unique_ptr<State::Game_State>> m_states;

		Renderer::Master m_renderer;

		Camera camera;

		int frames = 0;
};