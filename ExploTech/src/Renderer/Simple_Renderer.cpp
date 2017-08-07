#include "Simple_Renderer.h"

#include "../Temp/Quad.h"

#include "../Math/Matrix.h"

#include "../World/Block/Block_Database.h"

#include "../Texture/TextureManager.h"

#include "../Camera.h"

namespace Renderer
{
	// TODO rename entity renderer.
	void Simple::addToSimpleRenderList(EntityManager& entityManager)
	{
		m_entityManager = &entityManager;
	}

	void Simple::update(const Camera& camera)
	{
		m_shader.bind();
		m_shader.setTime(m_clock.getElapsedTime().asSeconds());

		m_shader.setViewMatrix(camera.getViewMatrix());
		m_shader.setProjMatrix(camera.getProjectionMatrix());

		TextureManager::get().getPtrTextureArray()->bind();

		for (auto& quad : (*(m_entityManager->getQuads()))) 
		{
			prepare(*quad);
			glDrawElements(GL_TRIANGLES,
						   quad->getModel().getIndicesCount(),
						   GL_UNSIGNED_INT,
						   nullptr);
		}

		m_entityManager = nullptr;
	
	}

	void Simple::prepare(Quad& quad)
	{
		quad.getModel().bind();
		m_shader.setModelMatrix(Math::createModelMatrix(quad));
	}
}