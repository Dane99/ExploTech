#pragma once

#include <cstdint>

namespace
{

	constexpr static int32_t    CHUNK_SIZE_X = 16, CHUNK_SIZE_Y = 256, CHUNK_SIZE_Z = 16;


	constexpr static int32_t CHUNK_VOLUME = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z,
							 CHUNK_AREA = CHUNK_SIZE_X * CHUNK_SIZE_Z;

	constexpr static int8_t     MAX_LIGHT = 10;

	constexpr static float      BLOCK_SIZE = 1.0f;

	constexpr static int PLAYER_REACH_DISTANCE = 10;
	constexpr static float REACH_RESOLUTION = 0.1f;
}
