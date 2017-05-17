#pragma once

#include "../../Glm_Common.h"
#include "../Block/Block_Data.h"

#include "Chunk.h"

#include <vector>
#include <unordered_map>

struct KeyHasher
{
	std::size_t operator()(const IntVector3& key) const
	{
		using std::size_t;
		using std::hash;

		return ((key.x * 5209) ^ (key.y * 1811)) ^ (key.z * 7297);
	}
};

class World_Manager {

	public:
		World_Manager();
		~World_Manager();
		
		// Returns true if it block at world location is solid.
		bool getBlockExistence(Vector3 worldPosition);
		Block::Block_Data getBlockData(Vector3 worldPosition);

		// TODO
		Vector3 getChunkPositionFromWorldPosition(Vector3 worldPosition);

		std::unordered_map<IntVector3, Chunk*, KeyHasher>* getChunks();

		void generateAllChunks();

	private:

		

		uint16_t m_worldSizeX = 2; // Length and width of the area of chunks we want to load.
		uint16_t m_worldSizeY = 1;
		uint16_t m_worldSizeZ = 2;

		// Hasher for the map below

		std::unordered_map<IntVector3, Chunk*, KeyHasher>* m_chunks;
};