#include "World_Manager.h"

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
World_Manager::World_Manager()
{
	m_chunks = new std::unordered_map<IntVector3, Chunk*, KeyHasher>;

	for (int x = 0; x < m_worldSizeX; ++x)
	{
		for (int y = 0; y < m_worldSizeY; ++y)
		{
			for (int z = 0; z < m_worldSizeZ; ++z)
			{

				(*m_chunks)[IntVector3(x, y, z)] = new Chunk(IntVector3(x, y, z));

				//std::cout << "Test" << m_chunks.size() << std::endl;
			}
		}
	}

	for (int x = 0; x < m_worldSizeX; x++) {
		for (int y = 0; y < m_worldSizeY; y++) {
			for (int z = 0; z < m_worldSizeZ; z++) {
				if (x > 0)
					(*m_chunks)[IntVector3(x, y, z)]->left = (*m_chunks)[IntVector3(x - 1, y, z)];
				if (x < m_worldSizeX - 1)
					(*m_chunks)[IntVector3(x, y, z)]->right = (*m_chunks)[IntVector3(x + 1, y, z)];
				if (y > 0)
					(*m_chunks)[IntVector3(x, y, z)]->below = (*m_chunks)[IntVector3(x, y - 1, z)];
				if (y < m_worldSizeY - 1)
					(*m_chunks)[IntVector3(x, y, z)]->above = (*m_chunks)[IntVector3(x, y + 1, z)];
				if (z > 0)
					(*m_chunks)[IntVector3(x, y, z)]->front = (*m_chunks)[IntVector3(x, y, z - 1)];
				if (z < m_worldSizeZ - 1)
					(*m_chunks)[IntVector3(x, y, z)]->back = (*m_chunks)[IntVector3(x, y, z + 1)];
			}
		}
	}
}

World_Manager::~World_Manager()
{
	std::unordered_map<IntVector3, Chunk*, KeyHasher>::iterator it = m_chunks->begin();
	while (it != m_chunks->end())
	{
		delete it->second;
		++it;
	}
	delete m_chunks;
}

World_Manager& World_Manager::get()
{
	static World_Manager worldManager;
	return worldManager;
}

void World_Manager::addThreadSafeBlockChangesToTheList(Vector3 worldPosition, Block::ID type)
{
	blockChangesMutex.lock();

	// Construct a new blockChanges structure
	BlockChange change(worldPosition, type);
	blockChanges.push(change);

	blockChangesMutex.unlock();
}

void World_Manager::realizeBlockChangeList()
{
	blockChangesMutex.lock();

	while (!blockChanges.empty())
	{
		SetBlock(blockChanges.front().worldPosition, static_cast<Block::ID>(blockChanges.front().type));
		blockChanges.pop();
	}
	blockChangesMutex.unlock();
}

void World_Manager::update()
{
	//realizeBlockChangeList();
}

Chunk* World_Manager::getChunkWithWorldPosition(Vector3 WorldPosition)
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

void World_Manager::SetBlock(Vector3 WorldPosition, Block::ID type, bool isFromServer)
{
	if (!isFromServer)
	{
		BlockChange blockChange(WorldPosition, type);
		// TODO
		ConnectionManager::get().sendMessageToServer(50000, "127.0.0.1", blockChange);
	}

	Chunk* chunk = getChunkWithWorldPosition(WorldPosition);
	//std::cout << "Called SetBlock: X:" << WorldPosition.x << " Y: " << WorldPosition.y << " Z: " << WorldPosition.z <<  '\n';
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
		std::cout << "ERROR with SetBlock" << '\n';
		return;
	}
}

Block::ID World_Manager::GetBlock(Vector3 WorldPosition)
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

void World_Manager::setBlockByPlayer(Vector3 blockPosition, Vector3 playerPosition, Block::ID type)
{
	GLfloat xDif, yDif, zDif, xDifAbs, yDifAbs, zDifAbs;
	xDif = playerPosition.x - blockPosition.x;
	yDif = playerPosition.y - blockPosition.y;
	zDif = playerPosition.z - blockPosition.z;

	xDifAbs = abs(xDif);
	yDifAbs = abs(yDif);
	zDifAbs = abs(zDif);

	//blockPosition = getCleanLocation(blockPosition);

	if (xDif >= yDif
		&& xDif >= zDif
		&& xDif >= xDifAbs
		&& xDif >= yDifAbs
		&& xDif >= zDifAbs) {

		if (GetBlock(Vector3(blockPosition.x + 0.5f, blockPosition.y, blockPosition.z)) == Block::ID::Air) {
			blockPosition.x += 1;
			SetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z), type);
		}
	}
	else if (yDif >= xDif
		&& yDif >= zDif
		&& yDif >= xDifAbs
		&& yDif >= yDifAbs
		&& yDif >= zDifAbs) {

		if (GetBlock(Vector3(blockPosition.x, blockPosition.y + 0.5f, blockPosition.z)) == Block::ID::Air) {
			blockPosition.y += 1;
			SetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z), type);
		}
	}
	else if (zDif >= xDif
		&& zDif >= yDif
		&& zDif >= xDifAbs
		&& zDif >= yDifAbs
		&& zDif >= zDifAbs) {
		if (GetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z + 0.5f)) == Block::ID::Air) {
			blockPosition.z += 1;
			SetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z), type);
		}
	}
	else if (xDifAbs >= xDif
		&& xDifAbs >= yDif
		&& xDifAbs >= zDif
		&& xDifAbs >= yDifAbs
		&& xDifAbs >= zDifAbs) {
		if (GetBlock(Vector3(blockPosition.x - 0.5f, blockPosition.y, blockPosition.z)) == Block::ID::Air) {
			blockPosition.x -= 1;
			SetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z), type);
		}

	}
	else if (yDifAbs >= xDif
		&& yDifAbs >= yDif
		&& yDifAbs >= zDif
		&& yDifAbs >= xDifAbs
		&& yDifAbs >= zDifAbs) {
		if (GetBlock(Vector3(blockPosition.x, blockPosition.y - 0.5f, blockPosition.z)) == Block::ID::Air) {
			blockPosition.y -= 1;
			SetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z), type);
		}

	}
	else if (zDifAbs >= xDif
		&& zDifAbs >= yDif
		&& zDifAbs >= zDif
		&& zDifAbs >= xDifAbs
		&& zDifAbs >= yDifAbs) {

		if (GetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z - 0.5f)) == Block::ID::Air) {
			blockPosition.z -= 1;
			SetBlock(Vector3(blockPosition.x, blockPosition.y, blockPosition.z), type);
		}
	}


}

std::unordered_map<IntVector3, Chunk*, KeyHasher>* World_Manager::getChunks()
{
	return m_chunks;
}

void World_Manager::generateAllChunks()
{
	for (std::unordered_map<IntVector3, Chunk*, KeyHasher>::iterator it = m_chunks->begin(); it != m_chunks->end(); ++it)
	{
		it->second->generate();
	}
}

