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

Chunk::Chunk(const Vector3 positon)
	:m_position(positon)
{
	m_blocks = new uint8_t**[CHUNK_SIZE];

	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		m_blocks[i] = new uint8_t*[CHUNK_SIZE];

		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			m_blocks[i][j] = new uint8_t[CHUNK_SIZE];
		}
	}
}

Chunk::~Chunk()
{
	for (int i = 0; i < CHUNK_SIZE; ++i)
	{
		for (int j = 0; j < CHUNK_SIZE; ++j)
		{
			delete [] m_blocks[i][j];
		}

		delete [] m_blocks[i];
	}
	delete [] m_blocks;
}

void Chunk::generate()
{
	mesh.reset();

	auto& atlas = Block::Database::get().textures;


	for (uint8_t x = 0; x < CHUNK_SIZE; ++x)
	{
		for (uint8_t y = 0; y < CHUNK_SIZE; ++y)
		{
			for (uint8_t z = 0; z < CHUNK_SIZE; ++z)
			{

				Vector3 blockPosition(x, y, z);

				auto &blockData = Block::Database::get().getBlockData(Block::ID::Grass);

				mesh.addFace(topFace,
					atlas.getTextureCoords(blockData.topTextureCoords),
					m_position,
					blockPosition);

				mesh.addFace(bottomFace,
					atlas.getTextureCoords(blockData.bottomTextureCoords),
					m_position,
					blockPosition);

				mesh.addFace(rightFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					m_position,
					blockPosition);

				mesh.addFace(leftFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					m_position,
					blockPosition);

				mesh.addFace(frontFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					m_position,
					blockPosition);

				mesh.addFace(backFace,
					atlas.getTextureCoords(blockData.sideTextureCoords),
					m_position,
					blockPosition);
			}
		}
	}

	mesh.buffer();
}

const Mesh& Chunk::getMesh() const
{
	return mesh;
}

const Vector3 & Chunk::getPosition() const
{
	return m_position;
}
