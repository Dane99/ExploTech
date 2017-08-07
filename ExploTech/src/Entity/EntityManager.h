#pragma once

#include "../Glm_Common.h"
#include <vector>
#include "../Temp/Quad.h"
#include "../Util/Singleton.h"

struct MoveEvent
{
	MoveEvent(Vector3 startPosition, Vector3 destination, float timeToComplete, float startTime, int id)
		: startPosition(startPosition),
		  destination(destination),
		  timeToComplete(timeToComplete),
		  startTime(startTime),
		  id(id)
	{
	}

	Vector3 startPosition;
	Vector3 destination;
	// Seconds
	float timeToComplete;
	float startTime;
	int id;
};

class EntityManager : Singleton
{
	public:
		static EntityManager& get();

		// Creates an entity object and returns the id.
		int addNewEntity(Vector3 worldPosition, EntityType type);

		void changePosition(Vector3 worldPosition, int id);

		void changeRotation(Vector3 rotation, int id);

		void moveToPosition(Vector3 destiniation, float timeToComplete, float startTime, int id);

		void update(float currentTime);

		std::vector<Quad*>* getQuads();

	private:
		EntityManager();
		~EntityManager();

		void updateMoveEvents(float currentTime);

		std::vector<MoveEvent> moveEvents;
		std::vector<Quad*> m_quads;
};