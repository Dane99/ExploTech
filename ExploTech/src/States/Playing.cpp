#include "Playing.h"

#include <SFML/System/Clock.hpp>
#include "../Renderer/Master_Renderer.h"

#include "../Camera.h"
#include "../World/Block/Block_Database.h"
#include <iostream>
#include "../Application.h"
#include "../World/WorldConstants.h"

namespace State {

	sf::Clock clock;

	Playing::Playing(Application &application)
		: Game_State (application)
		, m_quad(Block::Database::get().textures)
	{
		m_quad.position.z  = -3;
		worldManager.generateAllChunks();
	}

	void Playing::input()
	{
	}

	void Playing::update(float dt)
	{
		m_quad.position.x += sin(clock.getElapsedTime().asSeconds()) * dt * 0.8;
		m_quad.position.y += sin(clock.getElapsedTime().asSeconds()) * dt * 0.8;
		m_quad.position.z += cos(clock.getElapsedTime().asSeconds()) * dt * 0.8;
		//camera.input(dt);
		//m_quad.position.x = cos(clock.getElapsedTime().asSeconds());
		//m_quad.rotation.x = clock.getElapsedTime().asSeconds() * 100;
		//m_quad.rotation.z = clock.getElapsedTime().asSeconds() * 100;
	}

	void Playing::draw(Renderer::Master& renderer)
	{
		renderer.addToMasterRenderList(worldManager);
		renderer.addToMasterRenderList(m_quad);

	}

	void Playing::updateMouseClickInput(bool left, bool right)
	{
		//std::cout << static_cast<int>(worldManager.GetBlock(Vector3(0.5f, 0.5f, 0.5f))) << '\n';

		//worldManager.SetBlock(glm::vec3(0.5f, 0.5f, 0.5f), Block::ID::Air);
		Vector3 facingDirection = m_application->getCamera().getViewVector() * REACH_RESOLUTION;
		Vector3 currentPosition = m_application->getCamera().position;
		if (left) {
			for (int i = 0; i < static_cast<int>((1.0f / REACH_RESOLUTION) * PLAYER_REACH_DISTANCE); ++i)
			{
				currentPosition.x += facingDirection.x;
				currentPosition.y += facingDirection.y;
				currentPosition.z += facingDirection.z;
				//std::cout << "Test" << '\n';

				if (worldManager.GetBlock(glm::vec3(currentPosition.x, currentPosition.y, currentPosition.z)) != Block::ID::Air) {
					worldManager.SetBlock(glm::vec3(currentPosition.x, currentPosition.y, currentPosition.z), Block::ID::Air);
					break;
				}
			}
		}

	}

	void Playing::updateMouseInput(double xpos, double ypos)
	{
		m_application->getCamera().mouseInput(xpos, ypos);
	}

	void Playing::updateKeyboardInput(float dt)
	{
		m_application->getCamera().keyboardInput(dt);
	}
}