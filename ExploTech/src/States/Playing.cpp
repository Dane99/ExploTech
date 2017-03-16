#include "Playing.h"

#include <SFML/System/Clock.hpp>
#include "../Renderer/Master.h"

namespace State {

	sf::Clock clock;

	Playing::Playing(Application &application)
		: Game_State(application)
	{
		m_texture.load("grass");
		m_texture.bind();

		m_quad.position.z  = -3;
	}

	void Playing::input(Entity& camera)
	{
	}

	void Playing::update(Entity& camera)
	{
		//m_quad.position.x = cos(clock.getElapsedTime().asSeconds());
		//m_quad.rotation.x = clock.getElapsedTime().asSeconds() * 100;
		//m_quad.rotation.z = clock.getElapsedTime().asSeconds() * 100;
	}

	void Playing::draw(Renderer::Master& renderer)
	{
		renderer.draw(m_quad);
	}
}