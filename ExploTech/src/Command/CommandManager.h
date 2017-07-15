#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Text/Text_Manager.h"
#include <string>


class CommandManager
{
public:
	CommandManager(Text_Manager* textManager);

	static void openCommandWindow();
	static void closeCommandWindow();

	static bool isCommandWindowOpen();

	// Called by input manager when a key is pressed.
	static void keyPressed(unsigned int keyID);
	

private:

	static bool m_isCommandWindowOpen;

	static Text_Manager* m_textManager;

	static unsigned int textID;
	
	static bool currentTextIdExists;

};