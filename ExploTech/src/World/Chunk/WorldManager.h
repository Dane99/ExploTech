#pragma once

#include "../../Glm_Common.h"
#include "../../Util/Singleton.h"

#include "Chunk.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "../../Camera.h"

struct KeyHasher
{
	std::size_t operator()(const IntVector3& key) const
	{
		using std::size_t;
		using std::hash;

		return ((key.x * 5209) ^ (key.y * 1811)) ^ (key.z * 7297);
	}
};


class WorldManager
{

	public:
		WorldManager();
		~WorldManager();

		void update(Vector3& cameraPosition);

		// Get chunk with world position.
		Chunk* WorldManager::getChunkWithWorldPosition(Vector3 WorldPosition);

		// Set block with world position.
		void WorldManager::setBlock(Vector3 WorldPosition, Block::ID type);

		// Get block with world position.
		Block::ID WorldManager::GetBlock(Vector3 WorldPosition);

		// Get the full unordered map of chunks.
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* getChunks();

		void addChunk(const IntVector3& chunkPosition);

		void removeChunk(const IntVector3& chunkPosition);

		bool isChunkHere(const IntVector3& chunkPosition);

	private:
		void checkIfNewChunksShouldBeAdded(Vector3 cameraPosition);

		float GetDistance(float x2, float x1, float y2, float y1);

		bool doesChunkExist(IntVector3 ChunkPosition);
		
		// Defined area of chunks we want to load.
		//const uint16_t m_worldSizeX = 2; 
		//const uint16_t m_worldSizeY = 1;
		//const uint16_t m_worldSizeZ = 2;

		WorldGeneration worldGeneration;

		// Hasher for the map below
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* m_chunks;
};