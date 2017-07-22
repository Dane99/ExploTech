#include "CommandManager.h"

CommandManager::CommandManager()
{
	//m_threads.emplace_back([&]()
	//{
	//	while (m_isRunning)
	//	{
	//		checkForTextElementsThatShouldBeDeleted();
	//		std::this_thread::sleep_for(std::chrono::microseconds(100));
	//	}
	//});
}

CommandManager::~CommandManager()
{
}

CommandManager& CommandManager::get()
{
	static CommandManager commandManager;
	return commandManager;
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

	//std::lock_guard<std::mutex> lck(textElementsMutex);
	
	/*std::string s(1, tolower((char)keyID));

	if (CommandManager::m_isCommandWindowOpen && currentTextIdExists && keyID != GLFW_KEY_BACKSPACE)
	{
		m_textManager->concatenateText(s, textElements.back().id);
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

	if (keyID == GLFW_KEY_ENTER)
	{

	}


	if(CommandManager::m_isCommandWindowOpen && (!currentTextIdExists))
	{
		textID = m_textManager->addText(s, 20, 15, 0.5f, 0.5f, Vector3(1.0f));
		CommandManager::currentTextIdExists = true;
	}

*/

}

void CommandManager::checkForTextElementsThatShouldBeDeleted()
{
	//std::lock_guard<std::mutex> lck(textElementsMutex);
	//if()

}
