#pragma once

#include <vector>

#include "../Shaders/Simple_Shader.h"
#include "../World/Chunk/Chunk.h"

class Camera;

namespace Renderer
{
	class RChunk
	{
	public:
		void draw(const Full_Chunk& section);

		void update(const Camera& camera);

	private:
		void prepare(const Full_Chunk& section);

	private:
		std::vector<const Full_Chunk*> m_chunks;

		Shader::Simple_Shader m_shader;
	};
}