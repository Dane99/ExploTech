#include "World_Manager.h"

#include <iostream>

World_Manager::World_Manager()
{
	for (int x = 0; x < m_worldSize; ++x) 
	{
		for (int y = 0; y < m_worldHeight; ++y)
		{
			for (int z = 0; z < m_worldSize; ++z)
			{
				Chunk* chunk = new Chunk(Vector3(x, y, z));
				m_chunks.push_back(chunk);

				//std::cout << "Test" << m_chunks.size() << std::endl;
			}
		}
	}
}

World_Manager::~World_Manager()
{
	for (std::vector<Chunk*>::iterator it = m_chunks.begin(); it != m_chunks.end(); ++it)
	{
		delete *it;
	}
}

bool World_Manager::getBlockExistence(Vector3 worldPosition)
{   // TODO
	return false;
}

const std::vector<Chunk*>* World_Manager::getChunks() const
{
	return &m_chunks;
}

void World_Manager::generateAllChunks()
{
	for (std::vector<Chunk*>::iterator it = m_chunks.begin(); it != m_chunks.end(); ++it)
	{
		(*it)->generate();
	}
}

