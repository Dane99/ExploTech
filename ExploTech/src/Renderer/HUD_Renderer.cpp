#include <GL/glew.h>

#include "../Display.h"
#include "HUD_Renderer.h"
#include "../HUD/Crosshair.h"

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

		m_hud->crosshair.getModel().bind();
		m_hud->crosshair.getTexture().bind();

		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES,
			m_hud->crosshair.getModel().getIndicesCount(),
			GL_UNSIGNED_INT,
			nullptr);

		glEnable(GL_DEPTH_TEST);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}