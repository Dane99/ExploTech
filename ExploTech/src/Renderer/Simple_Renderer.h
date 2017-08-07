#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Simple_Shader.h"
#include "../Entity/EntityManager.h"

class Quad;
class Camera;

namespace Renderer
{
	class Simple
	{
		public:
			// adds a model to the m_models vector.
			void addToSimpleRenderList(EntityManager& entityManager);

			// draws all the models in m_models.
			void update(const Camera& camera);

		private:
			void prepare(Quad& quad);

			EntityManager* m_entityManager;
			Shader::Simple_Shader m_shader;

			sf::Clock m_clock;
	};
}
