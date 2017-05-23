#include "Chunk_Renderer.h"

#include "../Math/Matrix.h"

#include "../Camera.h"

#include "../World/Chunk/Chunk.h"

#include "../World/Block/Block_Database.h"

#include <iostream>

// # change name to world renderer

namespace Renderer
{
	void ChunkRenderer::addToChunkRenderList(World_Manager& worldManager)
	{
		world = &worldManager;
	}

	void ChunkRenderer::update(const Camera& camera)
	{
		glEnable(GL_CULL_FACE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glCullFace(GL_BACK); BUG with these needs fixing

		m_shader.bind();
		m_shader.setTime(m_clock.getElapsedTime().asSeconds());

		m_shader.setProjMatrix(camera.getProjectionMatrix());
		m_shader.setViewMatrix(camera.getViewMatrix());

		//Block::Database::get().textures.bind();


		//std::cout << world->getChunks()->size() << std::endl;
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* chunks = world->getChunks();
		for (auto it = chunks->begin(); it != chunks->end(); ++it) {

			Chunk *chunk = (it->second);

			// check if any chunks need to regenerate.
			chunk->checkForRebuild();

			prepare(*chunk);

			glDrawElements(GL_TRIANGLES,
				chunk->getMesh().getModel().getIndicesCount(),
				GL_UNSIGNED_INT,
				nullptr);

			chunk->getMesh().getModel().unbind();
		}

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_CULL_FACE);

		world = nullptr; // Not needed unless two separate worlds are used by application.
	}


	void ChunkRenderer::prepare(const Chunk& chunk)
	{
		m_shader.setModelMatrix(Math::createModelMatrix(chunk.getPosition()));
		chunk.getMesh().getModel().bind();
	}
}