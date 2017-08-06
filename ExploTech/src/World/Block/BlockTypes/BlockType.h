#pragma once

#include "Data/BlockData.h"

namespace Block
{
	class BlockType
	{
	public:
		const BlockData& getData() const;

	protected:
		BlockType(const std::string& fileName);

	private:
		BlockData m_blockData;
	};
}