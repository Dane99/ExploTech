#include "Block_Database.h"

#include <memory>
#include <vector>


namespace Block
{
	Database& Database::get()
	{
		static Database database;
		return database;
	}

	Database::Database()
		: blocks((int)ID::NUM_BLOCK_TYPES)
	{
		blocks[(int)ID::Air] = std::make_unique<Air>();
		blocks[(int)ID::Grass] = std::make_unique<Grass>();
	}

	const BlockData& Database::getBlockData(uint8_t id)
	{
		return blocks[id]->getData();
	}

	const BlockData& Database::getBlockData(ID blockID)
	{
		return blocks[(int)blockID]->getData();
	}

}