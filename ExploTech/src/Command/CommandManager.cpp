#include "CommandManager.h"

#include <sstream>
CommandManager::CommandManager()
{

}

CommandManager::~CommandManager()
{
	for (auto& element : m_textElements)
	{
		delete element;
	}
	m_textElements.clear();
}

void CommandManager::sendToInterpreter(std::string data)
{
	if (data.find("/tp") == 0)
	{
		float numbers[3];

		int index = 0;

		std::istringstream iss(data.substr(3, data.length() - 3));
		float num = 0;
		while ((iss >> num || !iss.eof()) && (index < 3)) {
			if (iss.fail()) {
				iss.clear();
				std::string dummy;
				iss >> dummy;
				continue;
			}
			numbers[index++] = num;
		}

		
		if (index < 3) {
			std::cout << "Teleport command failed!" << std::endl;
			return;
		}

		Application::get().getCamera().setPosition(Vector3(numbers[0], numbers[1], numbers[2]));

	}

	if (data.find("/c") == 0)
	{
		std::string buf; // Have a buffer string
		std::stringstream ss(data); // Insert the string into a stream

		std::vector<std::string> tokens; // Create vector to hold our words

		while (ss >> buf)
		{
			tokens.push_back(buf);
		}

		std::string message;
		for (unsigned int i = 2; i < tokens.size(); ++i)
		{
			message += tokens[i];

			if (i != tokens.size() - 1)
			{
				message += " ";
			}
		}
	}
}

void CommandManager::CheckforElementsThatShouldBeDeleted()
{
	auto i = m_textElements.begin();

	while (i != m_textElements.end())
	{
		if ((*i)->shouldBeDeleted())
		{
			delete *i;
			i = m_textElements.erase(i);
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
	if(m_textElements.size() != 0)
	{
		if (m_textElements.back()->isActive) {
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
			if (m_textElements.size() == 0)
			{
				TextElement* tmp = new TextElement(s);
				m_textElements.emplace_back(tmp);
			}
			else
			{
				if (m_textElements.back()->isActive)
				{
					delete m_textElements.back();
					m_textElements.pop_back();
				}
				else
				{
					TextElement* tmp = new TextElement(s);
					m_textElements.emplace_back(tmp);
				}
			}
		}
		else if(keyID == GLFW_KEY_SLASH && Input_Manager::keys[GLFW_KEY_RIGHT_SHIFT])
		{
			if (isCommandWindowOpen())
			{
				m_textElements.back()->add("?");
			}
		}
		else
		{
			if (isCommandWindowOpen())
			{
					m_textElements.back()->add(s);
		
			}
		}
	}

	if (keyID == GLFW_KEY_BACKSPACE)
	{
		if (isCommandWindowOpen())
		{
			m_textElements.back()->backSpace();
		}
	}

	if (keyID == GLFW_KEY_ENTER)
	{
		if (isCommandWindowOpen())
		{
			sendToInterpreter(Text_Manager::get().getTextString(m_textElements.back()->id));

			for (auto& element : m_textElements)
			{
				element->moveUp(25.0f);
			}
			TextElement* tmp = new TextElement("");
			m_textElements.emplace_back(tmp);
		}
	}

	if (keyID == GLFW_KEY_ESCAPE && isCommandWindowOpen())
	{
		delete m_textElements.back();
		m_textElements.pop_back();
	}		
}

void CommandManager::update()
{
	CheckforElementsThatShouldBeDeleted();
}

