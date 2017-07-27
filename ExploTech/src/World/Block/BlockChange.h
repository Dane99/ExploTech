#pragma once
#include "../../Glm_Common.h"
#include "Block_ID.h"

struct BlockChange
{
	BlockChange() = default;

	BlockChange(Vector3 worldPosition, uint8_t type)
		: worldPosition(worldPosition)
		, type(type)
	{
	}

	BlockChange(Vector3 worldPosition, Block::ID type)
		: worldPosition(worldPosition)
		, type(static_cast<uint8_t>(type))
	{
	}

	Vector3 worldPosition;
	uint8_t type;
};