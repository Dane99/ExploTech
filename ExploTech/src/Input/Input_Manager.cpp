#include "Input_Manager.h"
#include "../Display.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


bool Input_Manager::keys[1024];
std::map<unsigned int, std::vector<std::function<void(void)>>> Input_Manager::keyCallbacks;
Input_Manager Input_Manager::inputManager;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Input_Manager::Input_Manager() 
{
	glfwSetKeyCallback(Display::get(), key_callback);
	glfwSetCursorPosCallback(Display::get(), mouse_callback);
	glfwSetMouseButtonCallback(Display::get(), mouse_button_callback);

	// We use setWindowPointer to allow access to the class from an outside function. In this case that function is "mouse_callback".
	//glfwSetWindowUserPointer(Display::get(), this);
}

Input_Manager& Input_Manager::get()
{
	return inputManager;
}

void Input_Manager::addKeyPressCallback(unsigned int keyID, std::function<void(void)> func)
{
	if (keyID < 1024) {
		Input_Manager::keyCallbacks[keyID].push_back(func);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS && !CommandManager::get().isCommandWindowOpen())
	{
		Display::close();
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			CommandManager::get().keyPressed(key);

			auto it = Input_Manager::keyCallbacks.find(key);
			if (it != Input_Manager::keyCallbacks.end())
			{
				for(auto& func : it->second)
				{
					func();
				}
			}
			Input_Manager::keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			Input_Manager::keys[key] = false;
		}
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// window param is the same as Display::get().
	
	//Input_Manager* inputManager = static_cast<Input_Manager*>(glfwGetWindowUserPointer(window));
	Application::get().getCurrentGameStatePtr()->updateMouseInput(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// window param is the same as Display::get().
	//Input_Manager* inputManager = static_cast<Input_Manager*>(glfwGetWindowUserPointer(window));

	bool leftMouseButtonPressed = false
		, rightMouseButtonPressed = false;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		leftMouseButtonPressed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		rightMouseButtonPressed = true;
	}

	//std::cout << "Left: " << (int)leftMouseButtonPressed << " Right: " << (int)rightMouseButtonPressed << '\n';

	Application::get().getCurrentGameStatePtr()->updateMouseClickInput(leftMouseButtonPressed, rightMouseButtonPressed);
}
