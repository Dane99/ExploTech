#pragma once

#include "Simple.h"
#include "Solid.h"
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

			void draw(const Quad& model);
			void draw(const Full_Chunk& section);
		
		private:
			Simple m_simpleRenderer;
			RChunk m_chunkRenderer;
	};
}
