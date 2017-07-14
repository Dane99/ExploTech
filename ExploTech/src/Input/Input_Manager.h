#pragma once

#include "../States/Game_State.h"
#include "../Camera.h"
#include <functional>
#include <vector>
#include <map>

class Input_Manager {
	public:
		Input_Manager(Camera* camera, State::Game_State* gameState);
		
		void updateGameState(State::Game_State* gameState);
		void updateCamera(Camera* camera);

		State::Game_State* getCurrentGameState() const;
		Camera* getCurrentCamera() const;

		static void addKeyPressCallback(unsigned int keyID, std::function<void(void)> func);

		static bool keys[1024];
		static std::map<unsigned int, std::vector<std::function<void(void)>>> keyCallbacks;
	private:
		State::Game_State* currentGameState;
		Camera* currentCamera;
};