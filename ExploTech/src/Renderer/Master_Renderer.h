#pragma once

#include "Chunk_Renderer.h"
#include "HUD_Renderer.h"
#include "../HUD/HUD.h"
#include "../World/Chunk/Chunk.h"
#include "../World/Chunk/WorldManager.h"
#include "../Text/Text_Manager.h"
#include "TextRenderer.h"

class Quad;
class Camera;

namespace Renderer
{
	class Master
	{
		public:
			void clear();

			void update(const Camera& camera);
			void addToMasterRenderList(WorldManager& worldManager);
			void addToMasterRenderList(HUD& hud);
			void addToMasterRenderList(Text_Manager& textManager);
		
		private:
			ChunkRenderer m_chunkRenderer;
		    HUD_Renderer m_HudRenderer;
			Text_Renderer m_TextRenderer;
	};
}
