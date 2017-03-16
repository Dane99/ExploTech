#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Simple_Shader.h"

class Quad;
struct Entity;

namespace Renderer
{
	class Simple
	{
		public:
			// adds a model to the m_models vector.
			void draw(const Quad& quad);

			// draws all the models in m_models.
			void update(const Entity& camera);

		private:
			void prepare(const Quad& quad);

			std::vector<const Quad*> m_quads;
			Shader::Simple_Shader m_shader;

			sf::Clock m_clock;
	};
}
