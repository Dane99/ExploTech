#include "CommandManager.h"

#include <sstream>
CommandManager::CommandManager()
{

}

CommandManager::~CommandManager()
{
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
	for (int i = 0; i < _textElements.getSize(); i++) {
		if (_textElements.getPointerWithOffset(i)->shouldBeDeleted()) {
			_textElements.eraseWithOffset(i);
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
	if (_textElements.getSize() > 0 && _textElements.getLastPointer()->isActive)
	{
		return true;
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
			// If there are no text elements present, create one
			if (_textElements.getSize() == 0)
			{
				TextElement* tmp = new TextElement(s);
				_textElements.push_back(tmp);
			}
			else
			{
				// If there are text elements check whether the textElement has been sent.
				if (_textElements.getLastPointer()->isActive)
				{
					_textElements.pop();
				}
				else
				{
					TextElement* tmp = new TextElement(s);
					_textElements.push_back(tmp);
				}
			}
		}
		else if(keyID == GLFW_KEY_SLASH && Input_Manager::keys[GLFW_KEY_RIGHT_SHIFT])
		{
			if (isCommandWindowOpen())
			{
				_textElements.getLastPointer()->add("?");
			}
		}
		else
		{
			if (isCommandWindowOpen())
			{
					_textElements.getLastPointer()->add(s);
		
			}
		}
	}

	if (keyID == GLFW_KEY_BACKSPACE)
	{
		if (isCommandWindowOpen())
		{
			_textElements.getLastPointer()->backSpace();
		}
	}

	if (keyID == GLFW_KEY_ENTER)
	{
		if (isCommandWindowOpen())
		{
			sendToInterpreter(Text_Manager::get().getTextString(_textElements.getLastPointer()->id));

			for (int i = 0; i < _textElements.getSize(); i++) {
				_textElements.getPointerWithOffset(i)->moveUp(25.0f);
			}

			TextElement* tmp = new TextElement("");
			_textElements.push_back(tmp);
		}
	}

	if (keyID == GLFW_KEY_ESCAPE && isCommandWindowOpen())
	{
		_textElements.pop();
	}		
}

void CommandManager::update()
{
	CheckforElementsThatShouldBeDeleted();
}

