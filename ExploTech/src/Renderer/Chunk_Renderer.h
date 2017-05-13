#pragma once

#include <vector>
#include <SFML/System/Clock.hpp>

#include "../Shaders/Simple_Shader.h"
#include "../World/Chunk/World_Manager.h"

class Camera;

namespace Renderer
{
	class ChunkRenderer
	{
	public:
		void addToMasterRenderList(World_Manager& world);

		void update(const Camera& camera);

	private:
		void prepare(const Chunk& section);

	private:
		World_Manager* world;

		Shader::Simple_Shader m_shader;

		sf::Clock m_clock;
	};
}