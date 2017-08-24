#include "EntityManager.h"

EntityManager& EntityManager::get()
{
	static EntityManager entityManager;
	return entityManager;
}

int EntityManager::addNewEntity(Vector3 worldPosition, EntityType type)
{
	m_quads.push_back(new Quad(worldPosition));

	return m_quads.size() - 1;
}

void EntityManager::changePosition(Vector3 worldPosition, int id)
{
	m_quads.at(id)->position = worldPosition;
}

void EntityManager::changeRotation(Vector3 rotation, int id)
{
	m_quads.at(id)->rotation = rotation;
}

void EntityManager::moveToPosition(Vector3 destination, float timeToComplete, float startTime, int id)
{
	moveEvents.emplace_back(m_quads.at(id)->position, destination, timeToComplete, startTime, id);
}

void EntityManager::update(float currentTime)
{
	updateMoveEvents(currentTime);
}

std::vector<Quad*>* EntityManager::getQuads()
{
	return &m_quads;
}

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	for (auto& quad : m_quads)
	{
		delete quad;
	}
}

void EntityManager::updateMoveEvents(float currentTime)
{
	for (int i = 0; i < moveEvents.size(); ++i) 
	{
		float timeDiff = (currentTime - moveEvents[i].startTime);
		float movePercentageComplete = timeDiff / moveEvents[i].timeToComplete;

		if (movePercentageComplete > 1.0f)
		{
			// Set the end destination to the exact position.
			m_quads.at(moveEvents[i].id)->position = moveEvents[i].destination;
			moveEvents.erase(moveEvents.begin() + i);
			continue;
		}

		Vector3 positionDiff = moveEvents[i].destination - moveEvents[i].startPosition;

		m_quads.at(moveEvents[i].id)->position = moveEvents[i].startPosition + positionDiff*movePercentageComplete;
	}
}
