#include "Master_Renderer.h"
#include "../Display.h"

#include "../World/Block/Block_Database.h"

namespace Renderer 
{
	void Master::clear()
	{
		Display::clear();
	}

	void Master::update(const Camera& camera)
	{
		Block::Database::get().textures.bind();

		m_simpleRenderer.update(camera);
		m_chunkRenderer.update(camera);

		Display::update();
	}

	void Master::addToMasterRenderList(World_Manager& worldManager)
	{
		m_chunkRenderer.addToChunkRenderList(worldManager);
	}

	void Master::addToMasterRenderList(const Quad& model)
	{
		m_simpleRenderer.addToSimpleRenderList(model);
	}
}