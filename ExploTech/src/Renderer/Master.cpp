#include "Master.h"
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

	void Master::draw(const Full_Chunk& section)
	{
		m_chunkRenderer.draw(section);
	}

	void Master::draw(const Quad& model)
	{
		m_simpleRenderer.draw(model);
	}
}