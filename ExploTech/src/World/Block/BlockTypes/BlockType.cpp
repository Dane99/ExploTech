#include "BlockType.h"

namespace Block
{
	BlockType::BlockType(const std::string& fileName)
		: m_blockData(fileName)
	{
	}

	const BlockData& BlockType::getData() const
	{
		return m_blockData;
	}
}