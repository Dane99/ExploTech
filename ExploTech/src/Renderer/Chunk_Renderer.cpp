#include "Chunk_Renderer.h"

#include "../Math/Matrix.h"

#include "../Camera.h"

#include "../World/Chunk/Chunk.h"

#include <iostream>

// # change name to world renderer

namespace Renderer
{
	void ChunkRenderer::addToMasterRenderList(World_Manager& worldManager)
	{
		world = &worldManager;
	}

	void ChunkRenderer::update(const Camera& camera)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		m_shader.bind();
		m_shader.setTime(m_clock.getElapsedTime().asSeconds());

		m_shader.setProjMatrix(camera.getProjectionMatrix());
		m_shader.setViewMatrix(camera.getViewMatrix());

		std::cout << world->getChunks()->size() << std::endl;

		for (const auto* chunk : *(world->getChunks()))
		{
			prepare(*chunk);

			glDrawElements(GL_TRIANGLES,
				chunk->getMesh().getModel().getIndicesCount(),
				GL_UNSIGNED_INT,
				nullptr);

		}
		world = nullptr; // Not needed unless two seperate worlds are needed by application.
	}


	void ChunkRenderer::prepare(const Chunk& chunk)
	{
		m_shader.setModelMatrix(Math::createModelMatrix(chunk.getPosition()));
		chunk.getMesh().getModel().bind();
	}
}