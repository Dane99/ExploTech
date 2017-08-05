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

		// Add a new state on top.
		void pushState(std::unique_ptr<State::Game_State> state);
		// Removes the top state.
		void popState();

		Camera& getCamera();

		State::Game_State* getCurrentGameStatePtr();

	private:
		Application();
		~Application();

		std::stack<std::unique_ptr<State::Game_State>> m_states;

		Renderer::Master m_renderer;

		Camera camera;

		// Number of frames in the lifetime of the application.
		unsigned int frames = 0;
};