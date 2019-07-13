#pragma once

#include <SFML/System/Clock.hpp>
#include "../Shaders/Simple_Shader.h"
#include "../World/Chunk/WorldManager.h"

class Camera;

namespace Renderer
{
	class ChunkRenderer
	{
	public:
		void addToChunkRenderList(WorldManager& world);

		void update(const Camera& camera);

	private:
		void prepare(const Chunk& section);

	private:
		WorldManager* world;

		Shader::Simple_Shader m_shader;

		sf::Clock m_clock;
	};
}