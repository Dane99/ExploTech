#include "Chunk.h"
#include <vector>
#include <GL/glew.h>

#include "../WorldConstants.h"
#include "../Block/Block_Database.h"
#include "../Block/Block_ID.h"
#include "PositionTypes.h"

#include <iostream>

namespace
{
	const std::vector<GLfloat> frontFace
	{
		0,          0,          BLOCK_SIZE,
		BLOCK_SIZE, 0,          BLOCK_SIZE,
		BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
		0,          BLOCK_SIZE, BLOCK_SIZE
	};

	const std::vector<GLfloat> backFace
	{
		BLOCK_SIZE, 0,          0,
		0,          0,          0,
		0,          BLOCK_SIZE, 0,
		BLOCK_SIZE, BLOCK_SIZE, 0
	};

	const std::vector<GLfloat> leftFace
	{
		0, 0,           0,
		0, 0,           BLOCK_SIZE,
		0, BLOCK_SIZE,  BLOCK_SIZE,
		0, BLOCK_SIZE,  0
	};

	const std::vector<GLfloat> rightFace
	{
		BLOCK_SIZE, 0,          BLOCK_SIZE,
		BLOCK_SIZE, 0,          0,
		BLOCK_SIZE, BLOCK_SIZE, 0,
		BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE
	};

	const std::vector<GLfloat> topFace
	{
		0,          BLOCK_SIZE, BLOCK_SIZE,
		BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE,
		BLOCK_SIZE, BLOCK_SIZE, 0,
		0,          BLOCK_SIZE, 0
	};

	const std::vector<GLfloat> bottomFace
	{
		0,          0, 0,
		BLOCK_SIZE, 0, 0,
		BLOCK_SIZE, 0, BLOCK_SIZE,
		0,          0, BLOCK_SIZE
	};

	constexpr GLfloat TOP_LIGHT = 1.0f;
	constexpr GLfloat X_LIGHT = 0.8f;
	constexpr GLfloat Z_LIGHT = 0.6f;
	constexpr GLfloat BOTTOM_LIGHT = 0.6f;
}

Full_Chunk::Full_Chunk()
{
}

void Full_Chunk::Generate()
{
	mesh.reset();

	auto& atlas = Block::Database::get().textures;

	PositionTypes::Large_Position chunkPosition = { 0, 0, 0 };

	for (uint8_t x = 0; x < CHUNK_SIZE; ++x)
	{
		for (uint8_t y = 0; y < CHUNK_SIZE; ++y)
		{
			for (uint8_t z = 0; z < CHUNK_SIZE; ++z)
			{

				PositionTypes::Small_Position blockPosition(x, y, z);

				auto &blockData = Block::Database::get().getBlockData(Block::ID::Grass);

				mesh.addFace(topFace,
					atlas.getTextureCoords(blockData.topTextureCoords),
					chunkPosition,
					blockPosition);

				mesh.addFace(bottomFace,
					atlas.getTextureCoords(blockData.bottomTextureCoords),
					chunkPosition,
					blockPosition);

				mesh.addFace(rightFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					chunkPosition,
					blockPosition);

				mesh.addFace(leftFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					chunkPosition,
					blockPosition);

				mesh.addFace(frontFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					chunkPosition,
					blockPosition);

				mesh.addFace(backFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					chunkPosition,
					blockPosition);
			}
		}
	}

	mesh.buffer();
}

const Mesh& Full_Chunk::getMesh() const
{
	return mesh;
}
