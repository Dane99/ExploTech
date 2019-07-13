#pragma once

#include "../States/Game_State.h"
#include "../Camera.h"
#include <functional>
#include <vector>
#include <map>
#include "../Application.h"

class Input_Manager {
	public:
		static Input_Manager& get();

		static void addKeyPressCallback(unsigned int keyID, std::function<void(void)> func);

		static bool keys[1024];
		static std::map<unsigned int, std::vector<std::function<void(void)>>> keyCallbacks;
	private:
		Input_Manager();

		static Input_Manager inputManager;
};