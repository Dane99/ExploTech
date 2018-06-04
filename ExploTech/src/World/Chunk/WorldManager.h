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

#include "../Block/BlockChange.h"
#include "../../Networking/ConnectionManager.h"
#include "../../Camera.h"
#define CHUNK_INITIALIZING 0;
#define CHUNK_DONE_INITIALIZING 1;
#define CHUNK_MESH_GENERATED 2;
#define CHUNK_MESH_BUFFERED 3;

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

		// This function is for the server to add block changes on a seperate thread.
		void addThreadSafeServerBlockChangesToTheList(Vector3 worldPosition, Block::ID type, bool isFromServer = false);

		// Turns the server block change list into actual changes to the world.
		void realizeServerBlockChangeList();

		void update(Vector3& cameraPosition);

		// Get chunk with world position.
		Chunk* WorldManager::getChunkWithWorldPosition(Vector3 WorldPosition);

		// Set block with world position.
		void WorldManager::setBlock(Vector3 WorldPosition, Block::ID type, bool isFromServer = false);

		// Get block with world position.
		Block::ID WorldManager::GetBlock(Vector3 WorldPosition);

		// Get the full unordered map of chunks.
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* getChunks();

		void addChunk(const IntVector3& chunkPosition);

		void removeChunk(const IntVector3& chunkPosition);

		bool isChunkHere(const IntVector3& chunkPosition);

	private:

		void loadChunks();

		void rebuildChunks();

		void checkIfNewChunksShouldBeAdded(Vector3 cameraPosition);

		float GetDistance(float x2, float x1, float y2, float y1);

		bool doesChunkExist(IntVector3 ChunkPosition);
		
		// Defined area of chunks we want to load.
		//const uint16_t m_worldSizeX = 2; 
		//const uint16_t m_worldSizeY = 1;
		//const uint16_t m_worldSizeZ = 2;

		// Queue for block changes from the server.
		std::queue<BlockChange> blockChanges;
		// Mutex for the server block additions.
		std::mutex blockChangesMutex;

		// True while the program is running
		std::atomic<bool> m_isRunning{ true };

		std::vector<std::thread> m_chunkLoadThreads;

		Chunk* m_generatedChunks;
		std::vector<Chunk*> m_updatingChunks;
		//moodycamel::ConcurrentQueue<Chunk*> m_rebuildChunks;
		//moodycamel::ConcurrentQueue<Chunk*> m_rebuiltChunks;
		//std::vector<Chunk*> m_generatedChunks;

		WorldGeneration worldGeneration;

		int chunksAdded = 0;
		int chunksRemoved = 0;

		std::mutex updatingChunksMutex;

		// Hasher for the map below
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* m_chunks;
};