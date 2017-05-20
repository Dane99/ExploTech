#include "Input_Manager.h"
#include "../Display.h"
#include <GLFW/glfw3.h>
#include <iostream>


bool Input_Manager::keys[1024];
double Input_Manager::mousePositionX = 0.0;
double Input_Manager::mousePositionY = 0.0;


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

Input_Manager::Input_Manager(Camera* camera, State::Game_State* gameState) 
	: currentCamera(camera),
	currentGameState(gameState)
{
	glfwSetKeyCallback(Display::get(), key_callback);
	glfwSetCursorPosCallback(Display::get(), mouse_callback);
	glfwSetMouseButtonCallback(Display::get(), mouse_button_callback);

	// We use setWindowPointer to allow access to the class from an outside function. In this case that function is "mouse_callback".
	glfwSetWindowUserPointer(Display::get(), this);
}

void Input_Manager::updateGameState(State::Game_State* gameState)
{
	currentGameState = gameState;
}

void Input_Manager::updateCamera(Camera* camera)
{
	currentCamera = camera;
}

State::Game_State* Input_Manager::getCurrentGameState() const
{
	return currentGameState;
}

Camera* Input_Manager::getCurrentCamera() const
{
	return currentCamera;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		Display::close();
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Input_Manager::keys[key] = true;
		else if (action == GLFW_RELEASE)
			Input_Manager::keys[key] = false;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	// window param is the same as Display::get().

	Input_Manager::mousePositionX = xpos;
	Input_Manager::mousePositionY = ypos;

	Input_Manager* inputManager = static_cast<Input_Manager*>(glfwGetWindowUserPointer(window));
	inputManager->getCurrentGameState()->updateMouseInput(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	// window param is the same as Display::get().
	Input_Manager* inputManager = static_cast<Input_Manager*>(glfwGetWindowUserPointer(window));

	bool rightMouseButtonPressed, leftMouseButtonPressed = false;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		leftMouseButtonPressed = true;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		rightMouseButtonPressed = true;
	}

	inputManager->getCurrentGameState()->updateMouseClickInput(leftMouseButtonPressed, rightMouseButtonPressed);
}
