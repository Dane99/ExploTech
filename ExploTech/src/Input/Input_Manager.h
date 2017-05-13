#pragma once

#include "../States/Game_State.h"
#include "../Camera.h"

class Input_Manager {
	public:
		Input_Manager(Camera* camera, State::Game_State* gameState);
		
		void updateGameState(State::Game_State* gameState);
		void updateCamera(Camera* camera);

		State::Game_State* getCurrentGameState() const;
		Camera* getCurrentCamera() const;

		static bool keys[1024];
	private:
		State::Game_State* currentGameState;
		Camera* currentCamera;
};