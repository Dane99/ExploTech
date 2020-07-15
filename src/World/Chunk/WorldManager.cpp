#include "WorldManager.h"

#include <iostream>
#include <utility>
#include <unordered_map>

namespace {

	int mod(int a, int b)
	{
		if (b < 0) //you can check for b == 0 separately and do what you want
			return mod(a, -b);
		int ret = a % b;
		if (ret < 0)
			ret += b;
		return ret;
	}
}

WorldManager::WorldManager()
{
	m_chunks = new std::unordered_map<IntVector3, Chunk*, KeyHasher>;
}

WorldManager::~WorldManager()
{
	// Delete all chunks
	auto it = m_chunks->begin();
	while (it != m_chunks->end())
	{
		delete it->second;
		++it;
	}
	delete m_chunks;

}

void WorldManager::checkIfNewChunksShouldBeAdded(Vector3 cameraPosition)
{
	float RENDER_DISTANCE = 200.0f;
	float REMOVAL_DISTANCE = 300.0f;

	// Distance from player to chunk.
	float Distance = 0.0f;

	auto it = m_chunks->begin();

	// Iterate over the map using iterator
	while (it != m_chunks->end())
	{
		Distance = GetDistance(it->first.x*CHUNK_SIZE_X, cameraPosition.x, it->first.z*CHUNK_SIZE_Z, cameraPosition.z);
		// checking if the distance of the chunk is greater than REMOVAL_DISTANCE blocks away.
		// If it is we delete the chunk
		if (Distance > REMOVAL_DISTANCE) {
			// delete chunk 
			// TODO add chunk deletion for iterators
			if (it->second->left != nullptr) { it->second->left->changed = true;  it->second->left->right = nullptr; }
			if (it->second->right != nullptr) { it->second->right->changed = true;  it->second->right->left = nullptr; }

			if (it->second->above != nullptr) { it->second->above->changed = true;  it->second->above->below = nullptr; }
			if (it->second->below != nullptr) { it->second->below->changed = true;  it->second->below->above = nullptr; }

			if (it->second->front != nullptr) { it->second->front->changed = true; it->second->front->back = nullptr; }
			if (it->second->back != nullptr) { it->second->back->changed = true; it->second->back->front = nullptr; }
			//std::cout << "Chunk Deleted " << "X: " << it->first.x << " Y: " << it->first.y << " Z: " << it->first.z << std::endl;
			//std::cout << Distance << std::endl;
			delete it->second;
			it = m_chunks->erase(it);

		}
		else {
			++it;
		}
	}

	it = m_chunks->begin();
	while (it != m_chunks->end())
	{

		if (it->second->left == nullptr) {
			// Big mistake happened here. Took several hours to fix. (it->first.x - 1)*Chunk::CHUNK_SIZE_X is correct. it->first.x*(Chunk::CHUNK_SIZE_X - 1) is not.
			if ((GetDistance((it->first.x - 1)*CHUNK_SIZE_X, cameraPosition.x, it->first.z*CHUNK_SIZE_Z, cameraPosition.z)) < RENDER_DISTANCE) {
				// This chunk should not exist before we create it
				if (doesChunkExist(glm::ivec3(it->first.x - 1, it->first.y, it->first.z)) == false) {
					addChunk(glm::ivec3(it->first.x - 1, it->first.y, it->first.z));
					//std::cout << "Chunk Added " << "X: " << it->first.x - 1 << " Y: " << it->first.y << " Z: " << it->first.z << std::endl;
					//std::cout << (GetDistance((it->first.x - 1)*Chunk::CHUNK_SIZE_X, PlayerPosition.x, it->first.z*Chunk::CHUNK_SIZE_Z, PlayerPosition.z)) << std::endl;
				}
			}
		}
		if (it->second->right == nullptr) {
			if ((GetDistance((it->first.x + 1)*CHUNK_SIZE_X, cameraPosition.x, it->first.z*CHUNK_SIZE_Z, cameraPosition.z)) < RENDER_DISTANCE) {
				if (doesChunkExist(glm::ivec3(it->first.x + 1, it->first.y, it->first.z)) == false) {
					addChunk(glm::ivec3(it->first.x + 1, it->first.y, it->first.z));
				}
			}
		}

		if (it->second->front == nullptr) {
			if ((GetDistance(it->first.x*CHUNK_SIZE_X, cameraPosition.x, (it->first.z - 1)*CHUNK_SIZE_Z, cameraPosition.z)) < RENDER_DISTANCE) {
				if (doesChunkExist(glm::ivec3(it->first.x, it->first.y, it->first.z - 1)) == false) {
					addChunk(glm::ivec3(it->first.x, it->first.y, it->first.z - 1));
				}
			}
		}
		if (it->second->back == nullptr) {
			if ((GetDistance(it->first.x*CHUNK_SIZE_X, cameraPosition.x, (it->first.z + 1)*CHUNK_SIZE_Z, cameraPosition.z)) < RENDER_DISTANCE) {
				if (doesChunkExist(glm::ivec3(it->first.x, it->first.y, it->first.z + 1)) == false) {
					addChunk(glm::ivec3(it->first.x, it->first.y, it->first.z + 1));
				}
			}
		}
		++it;
	}
}

float WorldManager::GetDistance(float x2, float x1, float y2, float y1)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

bool WorldManager::doesChunkExist(IntVector3 ChunkPosition)
{
	auto it = m_chunks->find(ChunkPosition);
	if (it == m_chunks->end()) {
		return false;
	}
	else {
		return true;
	}
}

void WorldManager::update(Vector3& cameraPosition)
{
	checkIfNewChunksShouldBeAdded(cameraPosition);

	int totalRebuilt = 0;

	for (auto& chunk : *m_chunks)
	{
		if (chunk.second->changed && totalRebuilt < 1)
		{
			chunk.second->generate();
			++totalRebuilt;
		}
	}
}

Chunk* WorldManager::getChunkWithWorldPosition(Vector3 WorldPosition)
{
	//std::cout << WorldPosition.x << std::endl;
	std::unordered_map<IntVector3, Chunk*, KeyHasher>::iterator it = m_chunks->begin();
	while (it != m_chunks->end())
	{
		if (it->second->getPosition().x*CHUNK_SIZE_X < WorldPosition.x
			&& (it->second->getPosition().x*CHUNK_SIZE_X + CHUNK_SIZE_X) >= WorldPosition.x
			&& it->second->getPosition().y*CHUNK_SIZE_Y < WorldPosition.y
			&& (it->second->getPosition().y*CHUNK_SIZE_Y + CHUNK_SIZE_Y) >= WorldPosition.y
			&& it->second->getPosition().z*CHUNK_SIZE_Z < WorldPosition.z
			&& (it->second->getPosition().z*CHUNK_SIZE_Z + CHUNK_SIZE_Z) >= WorldPosition.z) {
			//std::cout << it->first.x << std::endl;
			return it->second;
		}
		++it;
	}
	return nullptr;
}

void WorldManager::setBlock(Vector3 WorldPosition, Block::ID type)
{
	Chunk* chunk = getChunkWithWorldPosition(WorldPosition);
	//std::cout << "Called setBlock: X:" << WorldPosition.x << " Y: " << WorldPosition.y << " Z: " << WorldPosition.z <<  '\n';
	// make sure it is range.
	if (chunk != nullptr) {
		int x = floor(WorldPosition.x);
		int y = floor(WorldPosition.y);
		int z = floor(WorldPosition.z);
		//std::cout << x << " " << y << " " << z << " " << std::endl;

		// the remainders of how far the location is out of the coords of a chunk (slightly confusing)
		int rx = mod(x, CHUNK_SIZE_X);
		int ry = mod(y, CHUNK_SIZE_Y);
		int rz = mod(z, CHUNK_SIZE_Z);

		//std::cout << rx << " " << ry << " " << rz << " " << std::endl;
		chunk->setBlock(rx, ry, rz, static_cast<uint8_t>(type));
	}
	else {
		std::cout << "ERROR with setBlock" << '\n';
		return;
	}
}

Block::ID WorldManager::GetBlock(Vector3 WorldPosition)
{

	// make sure it is range.
	Chunk* chunk = getChunkWithWorldPosition(WorldPosition);

	if (chunk != nullptr) {
		int x = floor(WorldPosition.x);
		int y = floor(WorldPosition.y);
		int z = floor(WorldPosition.z);

		// the remainders of how far the location is out of the coords of a chunk (slightly confusing)
		int rx = mod(x, CHUNK_SIZE_X);
		int ry = mod(y, CHUNK_SIZE_Y);
		int rz = mod(z, CHUNK_SIZE_Z);

		//std::cout << rx << " ";
		return static_cast<Block::ID>(chunk->getBlock(rx, ry, rz));
	}
	else {
		return Block::ID::Air;
	}
}

std::unordered_map<IntVector3, Chunk*, KeyHasher>* WorldManager::getChunks()
{
	return m_chunks;
}

void WorldManager::addChunk(const IntVector3& chunkPosition)
{
	if (m_chunks->find(chunkPosition) != m_chunks->end()) 
	{
		std::cout << "Chunk already exists" << std::endl;
		return;
	}

	(*m_chunks)[chunkPosition] = new Chunk(chunkPosition, &worldGeneration);


	if (m_chunks->find(IntVector3(chunkPosition.x - 1, chunkPosition.y, chunkPosition.z)) != m_chunks->end())
	{
		(*m_chunks)[chunkPosition]->left = (*m_chunks)[IntVector3(chunkPosition.x - 1, chunkPosition.y, chunkPosition.z)];
		(*m_chunks)[IntVector3(chunkPosition.x - 1, chunkPosition.y, chunkPosition.z)]->right = (*m_chunks)[chunkPosition];
		(*m_chunks)[IntVector3(chunkPosition.x - 1, chunkPosition.y, chunkPosition.z)]->changed = true;
	}
	if (m_chunks->find(IntVector3(chunkPosition.x + 1, chunkPosition.y, chunkPosition.z)) != m_chunks->end()) 
	{
		(*m_chunks)[chunkPosition]->right = (*m_chunks)[IntVector3(chunkPosition.x + 1, chunkPosition.y, chunkPosition.z)];
		(*m_chunks)[IntVector3(chunkPosition.x + 1, chunkPosition.y, chunkPosition.z)]->left = (*m_chunks)[chunkPosition];
		(*m_chunks)[IntVector3(chunkPosition.x + 1, chunkPosition.y, chunkPosition.z)]->changed = true;
	}
	if (m_chunks->find(IntVector3(chunkPosition.x, chunkPosition.y - 1, chunkPosition.z)) != m_chunks->end())
	{
		(*m_chunks)[chunkPosition]->below = (*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y - 1, chunkPosition.z)];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y - 1, chunkPosition.z)]->above = (*m_chunks)[chunkPosition];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y - 1, chunkPosition.z)]->changed = true;
	}
	if (m_chunks->find(IntVector3(chunkPosition.x, chunkPosition.y + 1, chunkPosition.z)) != m_chunks->end())
	{
		(*m_chunks)[chunkPosition]->above = (*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y + 1, chunkPosition.z)];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y + 1, chunkPosition.z)]->below = (*m_chunks)[chunkPosition];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y + 1, chunkPosition.z)]->changed = true;
	}
	if (m_chunks->find(IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z - 1)) != m_chunks->end())
	{
		(*m_chunks)[chunkPosition]->front = (*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z - 1)];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z - 1)]->back = (*m_chunks)[chunkPosition];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z - 1)]->changed = true;
	}
	if (m_chunks->find(IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z + 1)) != m_chunks->end())
	{
		(*m_chunks)[chunkPosition]->back = (*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z + 1)];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z + 1)]->front = (*m_chunks)[chunkPosition];
		(*m_chunks)[IntVector3(chunkPosition.x, chunkPosition.y, chunkPosition.z + 1)]->changed = true;
	}
	(*m_chunks)[chunkPosition]->changed = true;

}

void WorldManager::removeChunk(const IntVector3& chunkPosition)
{
	Chunk* ChunkToDelete = (*m_chunks)[chunkPosition];
	if (ChunkToDelete->left != nullptr) { ChunkToDelete->left->changed = true;  ChunkToDelete->left->right = nullptr; }
	if (ChunkToDelete->right != nullptr) { ChunkToDelete->right->changed = true;  ChunkToDelete->right->left = nullptr; }

	if (ChunkToDelete->above != nullptr) { ChunkToDelete->above->changed = true;  ChunkToDelete->above->below = nullptr; }
	if (ChunkToDelete->below != nullptr) { ChunkToDelete->below->changed = true;  ChunkToDelete->below->above = nullptr; }

	if (ChunkToDelete->front != nullptr) { ChunkToDelete->front->changed = true; ChunkToDelete->front->back = nullptr; }
	if (ChunkToDelete->back != nullptr) { ChunkToDelete->back->changed = true; ChunkToDelete->back->front = nullptr; }

	delete ChunkToDelete;
	m_chunks->erase(chunkPosition);

}

bool WorldManager::isChunkHere(const IntVector3& chunkPosition)
{
	if (m_chunks->find(chunkPosition) != m_chunks->end()) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}
