#include <GL/glew.h>

#include "../Display.h"
#include "HUD_Renderer.h"
#include "../HUD/Crosshair.h"
#include "../Command/CommandManager.h"
#include "../Application.h"

namespace Renderer
{

	void HUD_Renderer::addToHudRenderList(HUD& hud)
	{
		this->m_hud = &hud;
	}

	void HUD_Renderer::update()
	{
		m_shader.bind();
		m_shader.setTime(m_clock.getElapsedTime().asSeconds());
		m_shader.setProjMatrix(glm::ortho(0.0f, static_cast<GLfloat>(Display::WIDTH), 0.0f, static_cast<GLfloat>(Display::HEIGHT)));

		// Crosshair
		m_hud->crosshair.getModel().bind();
		m_hud->crosshair.getTexture().bind();

		glDisable(GL_DEPTH_TEST);

		glDrawElements(GL_TRIANGLES,
			m_hud->crosshair.getModel().getIndicesCount(),
			GL_UNSIGNED_INT,
			nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		m_shader.unbind();

		if (CommandManager::get().isCommandWindowOpen()) {
			m_shader.setProjMatrix(glm::ortho(0.0f, static_cast<GLfloat>(Display::WIDTH), 0.0f, static_cast<GLfloat>(Display::HEIGHT)));

			// Command Window
			m_hud->commandWindow.getModel().bind();
			m_hud->commandWindow.getTexture().bind();

			glDrawElements(GL_TRIANGLES,
				m_hud->crosshair.getModel().getIndicesCount(),
				GL_UNSIGNED_INT,
				nullptr);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}


		glEnable(GL_DEPTH_TEST);

	
	}
}