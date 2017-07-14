#pragma once

#include <GLFW/glfw3.h>


class CommandManager
{
public:
	CommandManager();

	static void openCommandWindow();
	static void closeCommandWindow();

	static bool isCommandWindowOpen();

	// Called by input manager when a key is pressed.
	static void keyPressed(unsigned int keyID);
	

private:

	static bool m_isCommandWindowOpen;

	//Text_Manager *textManager;

};