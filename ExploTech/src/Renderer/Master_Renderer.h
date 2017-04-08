#pragma once

#include "Simple_Renderer.h"
#include "Chunk_Renderer.h"
#include "../World/Chunk/Chunk.h"

class Quad;
class Camera;

namespace Renderer
{
	class Master
	{
		public:
			void clear();

			void update(const Camera& camera);

			void addToMasterRenderList(const Quad& model);
			void addToMasterRenderList(const Chunk& section);
		
		private:
			Simple m_simpleRenderer;
			ChunkRenderer m_chunkRenderer;
	};
}
