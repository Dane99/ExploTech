#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Text/Text_Manager.h"
#include <string>
#include <SFML/System/Clock.hpp>
#include <thread>
#include <mutex>
#include "../Input/Input_Manager.h"

namespace
{
	struct TextElement
	{
		unsigned int id;
		sf::Clock existenceClock;

		// Whether or not the text element has been pushed up to the history=(history of text messages sent).
		bool isActive = false;
	};
}

class CommandManager
{
public:
	static CommandManager& get();

	void openCommandWindow();
	void closeCommandWindow();

	bool isCommandWindowOpen();

	// Called by input manager when a key is pressed.
	void keyPressed(unsigned int keyID);
	

private:
	CommandManager();
	~CommandManager();

	bool m_isCommandWindowOpen = false;

	std::vector<TextElement> textElements;

	void checkForTextElementsThatShouldBeDeleted();

	bool m_isRunning = true;

	std::vector<std::thread> m_threads;
	std::mutex textElementsMutex;
};