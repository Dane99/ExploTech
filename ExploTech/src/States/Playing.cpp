#include "Playing.h"

#include <SFML/System/Clock.hpp>
#include "../Renderer/Master_Renderer.h"

#include "../Camera.h"
#include "../World/Block/Block_Database.h"
#include <iostream>
#include "../Application.h"
#include "../World/WorldConstants.h"
#include "../Display.h"
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../Input/Input_Manager.h"

void printHello() {
	std::cout << "Hello" << std::endl;
}

namespace State {
	
	sf::Clock generalClock;
	sf::Clock randClock;

	Playing::Playing()
		: Game_State()
		, m_quad()
		, worldManager()
	{
		EntityManager::get().addNewEntity(Vector3(0, 0, -3), EntityType::MovingBlock);
		EntityManager::get().moveToPosition(Vector3(-10, -10, -10), 15.0f, generalClock.getElapsedTime().asSeconds(), 0);

		worldManager.addChunk(IntVector3(0, 0, 0));
		worldManager.addChunk(IntVector3(1, 0, 0));
		worldManager.addChunk(IntVector3(-1,0, 0));

		srand(time(NULL));
		m_quad.position.z  = -3;
		Text_Manager::get().addText("Hello World!", 100, 50, 1, 1, Vector3(0.5, 0.5, 0.5));
		Text_Manager::get().addText("Random Number Alert: ", 10, Display::HEIGHT - 20, 0.5f, 0.5f, Vector3(1.0, 0.5, 0.5));

		Input_Manager::addKeyPressCallback(GLFW_KEY_H, printHello);
	}

	void Playing::input()
	{
	}

	void Playing::update(float dt)
	{
		CommandManager::get().update();
		worldManager.update(Application::get().getCamera().position);
		EntityManager::get().update(generalClock.getElapsedTime().asSeconds());

		m_quad.position.x += static_cast<float>(sin(generalClock.getElapsedTime().asSeconds()) * dt * 0.8);
		m_quad.position.y += static_cast<float>(sin(generalClock.getElapsedTime().asSeconds()) * dt * 0.8);
		m_quad.position.z += static_cast<float>(cos(generalClock.getElapsedTime().asSeconds()) * dt * 0.8);


		Text_Manager::get().setTextPositionY(sin(generalClock.getElapsedTime().asSeconds()) * 150 + 300, 0);
		Text_Manager::get().setScaleX(cos(generalClock.getElapsedTime().asSeconds())/2 + 1, 0);
		Text_Manager::get().setScaleY(cos(generalClock.getElapsedTime().asSeconds())/2 + 1, 0);
		Text_Manager::get().setColor(Vector3(sin(generalClock.getElapsedTime().asSeconds() + 0),
									sin(generalClock.getElapsedTime().asSeconds() + 2),
									sin(generalClock.getElapsedTime().asSeconds() + 4)), 0);


		//Application::get().getCamera().position.x / 16

		/*std::cout << ((float)Application::get().getCamera().position.x) / 16.0f << std::endl;
		int chunkX = floor(((float)Application::get().getCamera().position.x) / 16.0f);
		int chunkZ = floor(((float)Application::get().getCamera().position.z) / 16.0f);
		

		IntVector3 chunkLocation(chunkX, 0, chunkZ);

		if(!World_Manager::get().isChunkHere(chunkLocation))
		{
			World_Manager::get().addChunk(chunkLocation);
			World_Manager::get().addChunk(IntVector3(chunkLocation.x + 1, chunkLocation.y, chunkLocation.z));
			World_Manager::get().addChunk(IntVector3(chunkLocation.x - 1, chunkLocation.y, chunkLocation.z));
			World_Manager::get().addChunk(IntVector3(chunkLocation.x, chunkLocation.y, chunkLocation.z + 1));
			World_Manager::get().addChunk(IntVector3(chunkLocation.x, chunkLocation.y, chunkLocation.z - 1));
		}
		*/


		static bool first = true;

		if (randClock.getElapsedTime().asSeconds() > 5 || first)
		{
			int number = rand() % 100 + 1;
			Text_Manager::get().setTextContent("Random Number Alert: " + std::to_string(number), 1);
			randClock.restart();
			first = false;
		}

		//m_quad.position.x = cos(clock.getElapsedTime().asSeconds());
		//m_quad.rotation.x = clock.getElapsedTime().asSeconds() * 100;
		//m_quad.rotation.z = clock.getElapsedTime().asSeconds() * 100;
	}

	void Playing::draw(Renderer::Master& renderer)
	{
		renderer.addToMasterRenderList(worldManager);
		renderer.addToMasterRenderList(EntityManager::get());
		renderer.addToMasterRenderList(hud);
		renderer.addToMasterRenderList(Text_Manager::get());

	}

	void Playing::updateMouseClickInput(bool left, bool right)
	{
		if (raycasting) 
		{
			Vector3 facingDirection = Application::get().getCamera().getViewVector() * REACH_RESOLUTION;
			Vector3 currentPosition = Application::get().getCamera().position;
			if (left) 
			{
				for (int i = 0; i < static_cast<int>((1.0f / REACH_RESOLUTION) * PLAYER_REACH_DISTANCE); ++i)
				{
					currentPosition.x += facingDirection.x;
					currentPosition.y += facingDirection.y;
					currentPosition.z += facingDirection.z;

					if (worldManager.GetBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z)) != Block::ID::Air) 
					{
						worldManager.setBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z), Block::ID::Air);
						break;
					}
				}
			}
			if (right) 
			{
				for (int i = 0; i < static_cast<int>((1.0f / REACH_RESOLUTION) * PLAYER_REACH_DISTANCE); ++i)
				{
					currentPosition.x += facingDirection.x;
					currentPosition.y += facingDirection.y;
					currentPosition.z += facingDirection.z;

					if (worldManager.GetBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z)) != Block::ID::Air)
					{
						currentPosition.x -= facingDirection.x;
						currentPosition.y -= facingDirection.y;
						currentPosition.z -= facingDirection.z;
						worldManager.setBlock(Vector3(currentPosition.x, currentPosition.y, currentPosition.z), Block::ID::Grass);

						
						break;
					}
				}
			}
		}
		else 
		{
			GLfloat depth;

			glReadPixels(Display::WIDTH / 2, Display::HEIGHT / 2, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);

			glm::vec4 viewport = glm::vec4(0, 0, Display::WIDTH, Display::HEIGHT);
			glm::vec3 wincoord = glm::vec3(Display::WIDTH / 2, Display::HEIGHT / 2, depth);
			glm::vec3 objcoord = glm::unProject(wincoord, Application::get().getCamera().getViewMatrix(), Application::get().getCamera().getProjectionMatrix(), viewport);

			Vector3 facingDirection = Application::get().getCamera().getViewVector() * 0.07f;

			if (right) 
			{
				worldManager.setBlock(objcoord - facingDirection, Block::ID::Grass);
			}
			if (left)
			{
				worldManager.setBlock(objcoord + facingDirection, Block::ID::Air);
			}
		}

	}

	void Playing::updateMouseInput(double xpos, double ypos)
	{
		Application::get().getCamera().mouseInput(xpos, ypos);
	}

	void Playing::updateKeyboardInput(float dt)
	{
		Application::get().getCamera().keyboardInput(dt);
	}
}