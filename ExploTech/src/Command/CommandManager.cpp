#include "CommandManager.h"

bool CommandManager::m_isCommandWindowOpen = false;


CommandManager::CommandManager()
{
}

void CommandManager::openCommandWindow()
{
	m_isCommandWindowOpen = true;
}

void CommandManager::closeCommandWindow()
{
	m_isCommandWindowOpen = false;
}

bool CommandManager::isCommandWindowOpen()
{
	return m_isCommandWindowOpen;
}

void CommandManager::keyPressed(unsigned int keyID)
{
	if (keyID == GLFW_KEY_SLASH) 
	{
		CommandManager::m_isCommandWindowOpen = !CommandManager::m_isCommandWindowOpen;
	}



}
