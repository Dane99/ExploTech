#include "Solid.h"

#include "../Math/Matrix.h"

#include "../Camera.h"

#include "../World/Chunk/Chunk.h"

#include <iostream>

namespace Renderer
{
	void RChunk::draw(const Full_Chunk& section)
	{
		m_chunks.push_back(&section);
	}

	void RChunk::update(const Camera& camera)
	{
		//glEnable(GL_CULL_FACE);

		m_shader.bind();

		m_shader.setProjMatrix(camera.getProjectionMatrix());
		m_shader.setViewMatrix(camera.getViewMatrix());

		//std::cout << m_chunks.size() << std::endl;

		for (const auto* section : m_chunks)
		{
			prepare(*section);

			glDrawElements(GL_TRIANGLES,
				section->getMesh().getModel().getIndicesCount(),
				GL_UNSIGNED_INT,
				nullptr);

		}
		m_chunks.clear();
	}

	void RChunk::prepare(const Full_Chunk& section)
	{
		//std::cout << section.getMesh().getModel().getIndicesCount() << std::endl;
		Entity temp;

		m_shader.setModelMatrix(Math::createModelMatrix(temp));
		section.getMesh().getModel().bind();
	}
}