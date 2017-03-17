#include "Application.h"
#include "Display.h"

#include "States/Playing.h"

Application::Application()
{
	pushState(std::make_unique<State::Playing>(*this));
}

void Application::runMainGameLoop()
{
	sf::Clock clock;

	Input_Manager inputManager(&camera, m_states.top().get());

	// we might want to update the camera and state once those things
	// start to change a bit.
	while (Display::isOpen()) 
	{
		auto dt = clock.restart().asSeconds();

		m_renderer.clear();

		m_states.top()->input(camera);
		m_states.top()->update(camera, dt);
		m_states.top()->updateKeyboardInput(camera, dt);
		m_states.top()->draw(m_renderer);

		m_renderer.update(camera);
	}
}

void Application::pushState(std::unique_ptr<State::Game_State> state)
{
	m_states.push(std::move(state));
}

void Application::popState()
{
	m_states.pop();
}
