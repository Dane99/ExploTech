#include "CommandManager.h"

bool CommandManager::m_isCommandWindowOpen = false;
Text_Manager* CommandManager::m_textManager = nullptr;
unsigned int CommandManager::textID = 0;
bool CommandManager::currentTextIdExists = false;

CommandManager::CommandManager(Text_Manager* textManager)
{
	m_textManager = textManager;
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
	
	std::string s(1, tolower((char)keyID));

	if (CommandManager::m_isCommandWindowOpen && currentTextIdExists && keyID != GLFW_KEY_BACKSPACE)
	{
		m_textManager->concatenateText(s, textID);
	}


	if (keyID == GLFW_KEY_SLASH) 
	{
		if(CommandManager::m_isCommandWindowOpen)
		{
			CommandManager::m_isCommandWindowOpen = false;
			m_textManager->deleteText(textID);
			textID = 0;

			CommandManager::currentTextIdExists = false;
		}
		else
		{
			CommandManager::m_isCommandWindowOpen = true;
		}
	}

	if (keyID == GLFW_KEY_BACKSPACE)
	{
		m_textManager->backSpace(textID);
	}


	if(CommandManager::m_isCommandWindowOpen && (!currentTextIdExists))
	{
		textID = m_textManager->addText(s, 20, 15, 0.5f, 0.5f, Vector3(1.0f));
		CommandManager::currentTextIdExists = true;
	}



}
