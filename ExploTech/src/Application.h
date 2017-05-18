#pragma once

#include <stack>
#include <memory>
#include "States/Game_State.h"

#include "Renderer/Master_Renderer.h"

#include "Entity.h"
#include "Camera.h"
#include "Input/Input_Manager.h"

class Application {
	public:
		Application();
		~Application();

		void runMainGameLoop();

		void pushState(std::unique_ptr<State::Game_State> state);
		void popState();

		Camera& getCamera();

	//	static State::Game_State* getGameState();

	private:
		std::stack<std::unique_ptr<State::Game_State>> m_states;

		Renderer::Master m_renderer;

		Camera camera;

		Input_Manager *inputManager;

		int frames = 0;
};