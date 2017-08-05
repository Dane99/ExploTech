#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Text/Text_Manager.h"
#include <string>
#include <SFML/System/Clock.hpp>
#include <thread>
#include <mutex>
#include "../Util/Singleton.h"
#include "../Input/Input_Manager.h"
#include "../Networking/ConnectionManager.h"



namespace
{
	struct TextElement
	{
		TextElement(std::string s)
		{
			id = Text_Manager::get().addText(s, 20, 15, 0.5f, 0.5f, Vector3(1.0f));
		}

		~TextElement()
		{
			Text_Manager::get().deleteText(id);
		}

		// Adds a string to the end of the text element.
		void add(std::string s)
		{
			Text_Manager::get().concatenateText(s, id);
		}

		// Removes the last character of the text element.
		void backSpace()
		{
			Text_Manager::get().backSpace(id);
		}

		// Moves the text element up by y.
		void moveUp(float y)
		{
			Text_Manager::get().changeTextPositionY(y, id);
		
			// If text elements is still active (we are still typing) then start the clock for it to disappear.
			if (isActive == true)
			{
				existenceClock.restart();
				isActive = false;
			}
		}

		unsigned int id;
		sf::Clock existenceClock;

		// Whether or not the text element has been pushed up to the history=(history of text messages sent).
		bool isActive = true;

		bool shouldBeDeleted()
		{
			if (isActive == false)
			{
				if (existenceClock.getElapsedTime().asSeconds() > 5)
				{
					return true;
				}
			}
			return false;
		}

	};
}

class CommandManager : public Singleton
{
public:
	static CommandManager& get();

	void openCommandWindow();
	void closeCommandWindow();

	bool isCommandWindowOpen();

	// Called by input manager when a key is pressed.
	void keyPressed(unsigned int keyID);
	
	void update();

private:
	CommandManager();
	~CommandManager();

	void sendToInterpreter(std::string data);

	void CheckforElementsThatShouldBeDeleted();

	bool m_isCommandWindowOpen = false;

	std::vector<TextElement*> m_textElements;

	bool m_isRunning = true;
};