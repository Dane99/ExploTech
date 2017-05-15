#include "Chunk.h"
#include <vector>
#include <GL/glew.h>

#include "../WorldConstants.h"
#include "../Block/Block_Database.h"
#include "../Block/Block_ID.h"
#include "PositionTypes.h"
#include "../Generation/World_Generation.h"

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


Vector3 arrayIndexOneToThreeDim(int i) {
	Vector3 arrayCoords;
	arrayCoords.x = i % CHUNK_SIZE_X;
	arrayCoords.y = (i / CHUNK_SIZE_X) % CHUNK_SIZE_Y;
	arrayCoords.z = i / (CHUNK_SIZE_X * CHUNK_SIZE_Y);
	return arrayCoords;
}


Chunk::Chunk(const Vector3 positon)
	:m_position(positon)
{
	
	auto& generation = World_Generation::get();

	for (int x = 0; x < CHUNK_SIZE_X; ++x) {
		for (int y = 0; y < CHUNK_SIZE_Y; ++y) {
			for (int z = 0; z < CHUNK_SIZE_Z; ++z) {
				m_blocks.set(x, y, z, static_cast<uint8_t>(generation.getBlockTypeAt(x, y, z)));
			}
		}
	}

	for (int i = 0; i < CHUNK_VOLUME; ++i) {
		//m_blocks[i] = static_cast<uint8_t>(generation.getBlockTypeAt(arrayIndexOneToThreeDim(i)));
	}
	
	//typesOfBlocksInChunk = new std::set<uint8_t>{ m_blocks, m_blocks + CHUNK_VOLUME };

	// Test printing of the set typesOfBlocksInChunk
	//for (auto& each : (*typesOfBlocksInChunk)) {
	//	std::cout << static_cast<int>(each) << std::endl;
	//}
}

Chunk::~Chunk()
{
}

void Chunk::generate()
{
	mesh.reset();

	auto& atlas = Block::Database::get().textures;


	for (uint8_t x = 0; x < CHUNK_SIZE_X; ++x)
	{
		for (uint8_t y = 0; y < CHUNK_SIZE_Y; ++y)
		{
			for (uint8_t z = 0; z < CHUNK_SIZE_Z; ++z)
			{

				Vector3 blockPosition(x, y, z);

				auto &blockData = Block::Database::get().getBlockData(m_blocks.get(x, y, z));
				
				// 0 is air
				if (!getBlockExistence(x, y + 1, z)) {
					mesh.addFace(topFace,
						atlas.getTextureCoords(blockData.topTextureCoords),
						m_position,
						blockPosition);
				}
				if (!getBlockExistence(x, y - 1, z)) {
					mesh.addFace(bottomFace,
						atlas.getTextureCoords(blockData.bottomTextureCoords),
						m_position,
						blockPosition);
				}

				if (!getBlockExistence(x + 1, y, z)) {
					mesh.addFace(rightFace,
						atlas.getTextureCoords(blockData.sideTextureCoords),
						m_position,
						blockPosition);
				}
				if (!getBlockExistence(x - 1, y, z)) {
					mesh.addFace(leftFace,
						atlas.getTextureCoords(blockData.sideTextureCoords),
						m_position,
						blockPosition);
				}
				if (!getBlockExistence(x, y, z + 1)) {
					mesh.addFace(frontFace,
						atlas.getTextureCoords(blockData.sideTextureCoords),
						m_position,
						blockPosition);
				}
				if (!getBlockExistence(x, y, z - 1)) {
					mesh.addFace(backFace,
						atlas.getTextureCoords(blockData.sideTextureCoords),
						m_position,
						blockPosition);
				}
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

bool Chunk::getBlockExistence(int x, int y, int z)
{
	if (x >= CHUNK_SIZE_X || y >= CHUNK_SIZE_Y || z >= CHUNK_SIZE_Z
	    || x < 0 || y < 0 || z < 0) 
	{
		return false;
	}
	else if(static_cast<int>(m_blocks.get(x, y, z)) != static_cast<int>(Block::ID::Air))
	{
		return true;
	}
	else 
	{
		return false;
	}
}
