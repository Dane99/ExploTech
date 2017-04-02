#pragma once

#include <memory>
#include <vector>

#include "Block_Types/Block_Type.h"

#include "Block_ID.h"

#include "../../Texture/Texture_Atlas.h"

namespace Block
{
	class Database
	{
	public:
		static Database& get();

		Database();

		const Type& getBlock(uint8_t id);
		const Type& getBlock(ID blockID);

		const Data_Holder& getBlockData(uint8_t id);
		const Data_Holder& getBlockData(ID blockID);

	private:
		std::vector<std::unique_ptr<Type>> blocks;

	public:
		Texture::Atlas textures;
	};

	const Type& get(uint8_t id);
	const Type& get(ID blockID);
}