#include "Block_Database.h"

#include <memory>
#include <vector>

#include "Block_Types/Air.h"
#include "Block_Types/Grass.h"

#include "Block_ID.h"

namespace Block
{
	Database& Database::get()
	{
		static Database database;
		return database;
	}

	Database::Database()
		: blocks((int)ID::NUM_BLOCK_TYPES)
		, textures("Texture_Atlas", 512, 16)
	{
		blocks[(int)ID::Air] = std::make_unique<Air>();
		blocks[(int)ID::Grass] = std::make_unique<Grass>();
	}

	const Type& Database::getBlock(uint8_t id)
	{
		return *blocks[id];
	}

	const Type& Database::getBlock(ID blockID)
	{
		return *blocks[(int)blockID];
	}

	const Data_Holder& Database::getBlockData(uint8_t id)
	{
		return blocks[id]->getData().getDataHolder();
	}

	const Data_Holder& Database::getBlockData(ID blockID)
	{
		return blocks[(int)blockID]->getData().getDataHolder();
	}


	const Type& get(uint8_t id)
	{
		return Database::get().getBlock(id);
	}

	const Type& get(ID blockID)
	{
		return Database::get().getBlock(blockID);
	}

}