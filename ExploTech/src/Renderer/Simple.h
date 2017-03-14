#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Simple_Shader.h"

class Model;

namespace Renderer
{
	class Simple
	{
		public:
			// adds a model to the m_models vector.
			void draw(const Model& model);

			// draws all the models in m_models.
			void update();

		private:
			void prepare(const Model& model);

			std::vector<const Model*> m_models;
			Shader::Simple_Shader m_shader;

			sf::Clock m_clock;
	};
}
