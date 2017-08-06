#pragma once

#include <memory>
#include <vector>

#include "Block_ID.h"

#include "BlockTypes/Air.h"
#include "BlockTypes/Grass.h"
#include "BlockTypes/BlockType.h"

namespace Block
{
	class Database
	{
	public:
		static Database& get();

		

		const BlockData& getBlockData(uint8_t id);
		const BlockData& getBlockData(ID blockID);

	private:
		Database();

		std::vector<std::unique_ptr<BlockType>> blocks;
	};
}