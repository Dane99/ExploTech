#include "Playing.h"

#include <SFML/System/Clock.hpp>
#include "../Renderer/Master.h"

#include "../Camera.h"
#include <iostream>

namespace State {

	sf::Clock clock;

	Playing::Playing(Application &application)
		: Game_State (application)
		, m_texture  ("Texture_Atlas", 512, 16)
		, m_quad     (m_texture)
	{
		m_texture.bind();

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
		renderer.draw(m_quad);
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