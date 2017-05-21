#include <GL/glew.h>

#include "../Display.h"
#include "HUD_Renderer.h"
#include "../HUD/Crosshair.h"

namespace Renderer
{

	void HUD_Renderer::addToHudRenderList(HUD& hud)
	{
		this->hud = &hud;
	}

	void HUD_Renderer::update()
	{
		shader.bind();

		hud->crosshair.getModel().bind();
		hud->crosshair.getTexture().bind();

		glDisable(GL_DEPTH_TEST);
		glDrawElements(GL_TRIANGLES,
			hud->crosshair.getModel().getIndicesCount(),
			GL_UNSIGNED_INT,
			nullptr);

		glEnable(GL_DEPTH_TEST);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}