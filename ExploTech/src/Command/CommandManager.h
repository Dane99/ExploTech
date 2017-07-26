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
			//std::cout << "Constructor called! " << id << std::endl;
		}

		~TextElement() 
		{
			//std::cout << "Destructor textElement. " << id << std::endl;
				Text_Manager::get().deleteText(id);
		}

		/*TextElement(const TextElement& other) {
			std::cout << "Copy constructor called! " << other.id << std::endl;

			existenceClock = other.existenceClock;
			isActive = other.isActive;

			id = Text_Manager::get().addText(Text_Manager::get().getTextString(other.id),
										 	 Text_Manager::get().getTextPositionX(other.id),
											 Text_Manager::get().getTextPositionY(other.id),
											 Text_Manager::get().getTextScaleX(other.id),
											 Text_Manager::get().getTextScaleY(other.id),
											 Text_Manager::get().getTextColor(other.id));
			std::cout << "Copy constructor called! got id " << id << std::endl;
		}

		TextElement& operator =(const TextElement& other)
		{
			std::cout << "Copy assignment constructor called! " << other.id << std::endl;
			existenceClock = other.existenceClock;
			isActive = other.isActive;

			id = Text_Manager::get().addText(Text_Manager::get().getTextString(other.id),
											 Text_Manager::get().getTextPositionX(other.id),
										  	 Text_Manager::get().getTextPositionY(other.id),
											 Text_Manager::get().getTextScaleX(other.id),
										  	 Text_Manager::get().getTextScaleY(other.id),
											 Text_Manager::get().getTextColor(other.id));
			std::cout << "Copy assignment constructor called! got id " << id << std::endl;
			return *this;
		}

		TextElement& operator= (TextElement && rhs)
		{
			std::cout << "Move assignment from " << rhs.id << std::endl;
			std::swap(id, rhs.id);
			std::swap(existenceClock, rhs.existenceClock);
			std::swap(isActive, rhs.isActive);
			return *this;
		}*/


		// adds more to the end of the text element.
		void add(std::string s)
		{
			Text_Manager::get().concatenateText(s, id);
		}

		void backSpace()
		{
			Text_Manager::get().backSpace(id);
		}

		void moveUp(float y)
		{
			//std::cout << "ID: " << id << std::endl;
			Text_Manager::get().changeTextPositionY(y, id);
		
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

	std::vector<TextElement*> textElements;

	bool m_isRunning = true;
};