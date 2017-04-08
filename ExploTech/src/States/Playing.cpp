#include "Playing.h"

#include <SFML/System/Clock.hpp>
#include "../Renderer/Master_Renderer.h"

#include "../Camera.h"
#include "../World/Chunk/Chunk.h"
#include "../World/Block/Block_Database.h"
#include <iostream>

namespace State {

	sf::Clock clock;

	Playing::Playing(Application &application)
		: Game_State (application)
		, m_quad(Block::Database::get().textures)
	{
		chunk.Generate();
		m_quad.position.z  = -3;
	}

	void Playing::input(Camera& camera)
	{
	}

	void Playing::update(Camera& camera, float dt)
	{
		//camera.input(dt);
		//m_quad.position.x = cos(clock.getElapsedTime().asSeconds());
		//m_quad.rotation.x = clock.getElapsedTime().asSeconds() * 100;
		//m_quad.rotation.z = clock.getElapsedTime().asSeconds() * 100;
	}

	void Playing::draw(Renderer::Master& renderer)
	{
		renderer.addToMasterRenderList(chunk);
		renderer.addToMasterRenderList(m_quad);

	}
	void Playing::updateMouseInput(Camera& camera, double xpos, double ypos)
	{
		camera.mouseInput(xpos, ypos);
	}
	void Playing::updateKeyboardInput(Camera& camera, float dt)
	{
		camera.keyboardInput(dt);
	}
}