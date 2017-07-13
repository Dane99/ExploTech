#include "Simple_Renderer.h"

#include "../Temp/Quad.h"

#include "../Math/Matrix.h"

#include "../World/Block/Block_Database.h"

#include "../Texture/TextureManager.h"

#include "../Camera.h"

namespace Renderer
{
	void Simple::addToSimpleRenderList(const Quad& quad)
	{
		m_quads.push_back(&quad);
	}

	void Simple::update(const Camera& camera)
	{
		m_shader.bind();
		m_shader.setTime(m_clock.getElapsedTime().asSeconds());

		// binding the texture atlas.
		//Block::Database::get().textures.bind();

		TextureManager::get().getPtrTextureArray()->bind();

		m_shader.setViewMatrix(camera.getViewMatrix());
		m_shader.setProjMatrix(camera.getProjectionMatrix());

		for (auto& quad : m_quads) 
		{
			prepare(*quad);
			glDrawElements(GL_TRIANGLES, quad->getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
		}

		m_quads.clear();
	
	}

	void Simple::prepare(const Quad& quad)
	{
		quad.getModel().bind();
		m_shader.setModelMatrix(Math::createModelMatrix(quad));
	}
}