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
		
		Chunk* World_Manager::getChunkWithWorldPosition(Vector3 WorldPosition);

		void World_Manager::SetBlock(Vector3 WorldPosition, Block::ID type);

		Block::ID World_Manager::GetBlock(Vector3 WorldPosition);

		void World_Manager::setBlockByPlayer(Vector3 blockPosition, Vector3 playerPosition, Block::ID type);

		// TODO
		Vector3 getChunkPositionFromWorldPosition(Vector3 worldPosition);

		std::unordered_map<IntVector3, Chunk*, KeyHasher>* getChunks();

		void generateAllChunks();

	private:

		

		const uint16_t m_worldSizeX = 2; // Length and width of the area of chunks we want to load.
		const uint16_t m_worldSizeY = 1;
		const uint16_t m_worldSizeZ = 2;

		// Hasher for the map below

		std::unordered_map<IntVector3, Chunk*, KeyHasher>* m_chunks;
};