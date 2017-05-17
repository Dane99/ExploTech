#include "World_Manager.h"

#include <iostream>
#include <utility>
#include <unordered_map>

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
}

bool World_Manager::getBlockExistence(Vector3 worldPosition)
{   // TODO
	return false;
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

