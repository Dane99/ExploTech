#include "CommandManager.h"


CommandManager::CommandManager()
{

}

CommandManager::~CommandManager()
{
}

void CommandManager::CheckforElementsThatShouldBeDeleted()
{
	auto i = textElements.begin();

	while (i != textElements.end())
	{
		if ((*i)->shouldBeDeleted())
		{
			delete *i;
			i = textElements.erase(i);
		}
		else
		{
			++i;
		}
	}
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
	if(textElements.size() != 0)
	{
		if (textElements.back()->isActive) {
			return true;
		}
	}
	return false;
}

void CommandManager::keyPressed(unsigned int keyID)
{
	// Keys that are letters and numbers (not backspace character).
	if (keyID < 127)
	{

		std::string s(1, tolower((char)keyID));
		std::cout << "key: " << s << std::endl;


		if (keyID == GLFW_KEY_SLASH && !Input_Manager::keys[GLFW_KEY_RIGHT_SHIFT])
		{
			if (textElements.size() == 0)
			{
				TextElement* tmp = new TextElement(s);
				textElements.emplace_back(tmp);
			}
			else
			{
				if (textElements.back()->isActive)
				{
					textElements.pop_back();
				}
				else
				{
					TextElement* tmp = new TextElement(s);
					textElements.emplace_back(tmp);
				}
			}
		}
		else if(keyID == GLFW_KEY_SLASH && Input_Manager::keys[GLFW_KEY_RIGHT_SHIFT])
		{
			if (isCommandWindowOpen())
			{
				textElements.back()->add("?");
			}
		}
		else
		{
			if (isCommandWindowOpen())
			{
					textElements.back()->add(s);
		
			}
		}
	}

	if (keyID == GLFW_KEY_BACKSPACE)
	{
		if (isCommandWindowOpen())
		{
			textElements.back()->backSpace();
		}
	}

	if (keyID == GLFW_KEY_ENTER)
	{
		if (isCommandWindowOpen())
		{
			for (auto& element : textElements)
			{
				element->moveUp(25.0f);
			}
			TextElement* tmp = new TextElement("");
			textElements.emplace_back(tmp);
		}
	}
/*
	if (keyID == GLFW_KEY_SLASH)
	{
		if (textElements.size() != 0) 
		{
			if (textElements.back().isActive)
			{
				//textElements.pop_back();
			}
			else
			{
				textElements.push_back(std::move(TextElement(s)));
			}
		}
		else {
			textElements.push_back(std::move(TextElement(s)));
		}
	}

		if (isCommandWindowOpen())
		{
			std::cout << "test" << std::endl;
			textElements.back().add(s);

		}
	*/
	/*
	if (CommandManager::m_isCommandWindowOpen && keyID != GLFW_KEY_BACKSPACE)
	{
		Text_Manager::get().concatenateText(s, textElements.back().id);
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

void CommandManager::update()
{
	CheckforElementsThatShouldBeDeleted();
}

