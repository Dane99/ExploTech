#include "Application.h"
#include "Display.h"

#include "States/Playing.h"

#include <iostream>


Application::Application()
{
	pushState(std::make_unique<State::Playing>());

}

Application::~Application()
{
}

Application& Application::get()
{
	static Application application;
	return application;
}

void Application::runMainGameLoop()
{
	sf::Clock clock;

	// we might want to update the camera and state once those things
	// start to change a bit.
	while (Display::isOpen()) 
	{
		auto dt = clock.restart().asSeconds();

		m_renderer.clear();


		m_states.top()->input();

		m_states.top()->updateKeyboardInput(dt);
		camera.updateViewMatrix();

		m_states.top()->update(dt);
		m_states.top()->draw(m_renderer);

		m_renderer.update(camera);

		if(frames % 60 == 0) std::cout << "FPS: " << floor(1.0f / (float)dt) << "\n";

		++frames;
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

Camera& Application::getCamera()
{
	return camera;
}

State::Game_State* Application::getCurrentGameStatePtr()
{
	return m_states.top().get();
}
