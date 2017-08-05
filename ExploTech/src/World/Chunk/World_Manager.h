#pragma once

#include "../../Glm_Common.h"
#include "../Block/Block_Data.h"
#include "../../Util/Singleton.h"

#include "Chunk.h"

#include <vector>
#include <unordered_map>
#include <queue>
#include <mutex>

#include "../Block/BlockChange.h"
#include "../../Networking/ConnectionManager.h"

struct KeyHasher
{
	std::size_t operator()(const IntVector3& key) const
	{
		using std::size_t;
		using std::hash;

		return ((key.x * 5209) ^ (key.y * 1811)) ^ (key.z * 7297);
	}
};


class World_Manager : public Singleton
{

	public:
		
		static World_Manager& get();

		// This function is for the server to add block changes on a seperate thread.
		void addThreadSafeServerBlockChangesToTheList(Vector3 worldPosition, Block::ID type, bool isFromServer = false);

		// Turns the server block change list into actual changes to the world.
		void realizeServerBlockChangeList();

		void update();

		// Get chunk with world position.
		Chunk* World_Manager::getChunkWithWorldPosition(Vector3 WorldPosition);

		// Set block with world position.
		void World_Manager::SetBlock(Vector3 WorldPosition, Block::ID type, bool isFromServer = false);

		// Get block with world position.
		Block::ID World_Manager::GetBlock(Vector3 WorldPosition);

		// Get the full unordered map of chunks.
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* getChunks();

		// Generates all the chunks that are within the defined range.
		void generateAllChunks();

	private:
		World_Manager();
		~World_Manager();
		
		// Defined area of chunks we want to load.
		const uint16_t m_worldSizeX = 2; 
		const uint16_t m_worldSizeY = 1;
		const uint16_t m_worldSizeZ = 2;

		// Queue for block changes from the server.
		std::queue<BlockChange> blockChanges;
		// Mutex for the server block additions.
		std::mutex blockChangesMutex;


		// Hasher for the map below
		std::unordered_map<IntVector3, Chunk*, KeyHasher>* m_chunks;
};