#pragma once

#include <vector>

#include "../Shaders/Simple_Shader.h"
#include "../World/Chunk/Chunk.h"

class Camera;

namespace Renderer
{
	class ChunkRenderer
	{
	public:
		void addToMasterRenderList(const Chunk& section);

		void update(const Camera& camera);

	private:
		void prepare(const Chunk& section);

	private:
		std::vector<const Chunk*> m_chunks;

		Shader::Simple_Shader m_shader;
	};
}