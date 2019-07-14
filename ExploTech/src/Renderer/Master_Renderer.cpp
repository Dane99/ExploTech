#include "Master_Renderer.h"
#include "../Display.h"

namespace Renderer 
{
	void Master::clear()
	{
		Display::clear();
	}

	void Master::update(const Camera& camera)
	{
		m_chunkRenderer.update(camera);
		m_HudRenderer.update();
		m_TextRenderer.update();

		Display::update();
	}

	void Master::addToMasterRenderList(WorldManager& worldManager)
	{
		m_chunkRenderer.addToChunkRenderList(worldManager);
	}

	void Master::addToMasterRenderList(HUD& hud)
	{
		m_HudRenderer.addToHudRenderList(hud);
	}

	void Master::addToMasterRenderList(Text_Manager& textManager)
	{
		m_TextRenderer.addToTextRenderList(textManager);
	}
}