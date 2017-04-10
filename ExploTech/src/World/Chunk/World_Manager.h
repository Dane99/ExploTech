#pragma once

#include "../../Glm_Common.h"
#include "../Block/Block_Data.h"

#include "Chunk.h"

#include <vector>

class World_Manager {

	public:
		World_Manager();
		~World_Manager();
		
		// Returns true if it block at world location is solid.
		bool getBlockExistence(Vector3 worldPosition);
		Block::Block_Data getBlockData(Vector3 worldPosition);

		Vector3 getChunkPositionFromWorldPosition(Vector3 worldPosition);

		const std::vector<Chunk*>* getChunks() const;

		void generateAllChunks();

	private:

		std::vector<Chunk*> m_chunks;

		uint16_t m_worldSize = 5; // Length and width of the area of chunks we want to load.
};