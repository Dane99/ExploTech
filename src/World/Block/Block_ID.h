#pragma once
#include <stdint.h>
namespace Block
{
	enum class ID: uint8_t
	{
		Air = 0,
		Grass = 1,

		NUM_BLOCK_TYPES
	};
}