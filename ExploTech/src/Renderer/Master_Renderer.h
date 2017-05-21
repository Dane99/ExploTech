#pragma once

#include "Simple_Renderer.h"
#include "Chunk_Renderer.h"
#include "HUD_Renderer.h"
#include "../HUD/HUD.h"
#include "../World/Chunk/Chunk.h"
#include "../World/Chunk/World_Manager.h"

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
			void addToMasterRenderList(World_Manager& worldManager);
			void addToMasterRenderList(HUD& hud);
		
		private:
			Simple m_simpleRenderer;
			ChunkRenderer m_chunkRenderer;
		    HUD_Renderer m_HudRenderer;
	};
}
