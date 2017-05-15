#pragma once

#include <cstdint>

namespace
{

	constexpr static int32_t    CHUNK_SIZE_X = 8, CHUNK_SIZE_Y = 8, CHUNK_SIZE_Z = 8;


	constexpr static int32_t CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z,
							 CHUNK_AREA = CHUNK_SIZE_X * CHUNK_SIZE_Z;

	constexpr static int8_t     MAX_LIGHT = 10;

	constexpr static float      BLOCK_SIZE = 1.0f;
}
