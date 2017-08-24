#include "Chunk.h"
#include <vector>
#include <GL/glew.h>

#include "../WorldConstants.h"
#include "../Block/Block_Database.h"
#include "PositionTypes.h"
#include "../Generation/World_Generation.h"

#include <iostream>


	const std::vector<GLfloat> frontFace
	{
		0,          0,          BLOCK_DIM,
		BLOCK_DIM, 0,          BLOCK_DIM,
		BLOCK_DIM, BLOCK_DIM, BLOCK_DIM,
		0,          BLOCK_DIM, BLOCK_DIM
	};

	const std::vector<GLfloat> backFace
	{
		BLOCK_DIM, 0,          0,
		0,          0,          0,
		0,          BLOCK_DIM, 0,
		BLOCK_DIM, BLOCK_DIM, 0
	};

	const std::vector<GLfloat> leftFace
	{
		0, 0,           0,
		0, 0,           BLOCK_DIM,
		0, BLOCK_DIM,  BLOCK_DIM,
		0, BLOCK_DIM,  0
	};

	const std::vector<GLfloat> rightFace
	{
		BLOCK_DIM, 0,          BLOCK_DIM,
		BLOCK_DIM, 0,          0,
		BLOCK_DIM, BLOCK_DIM, 0,
		BLOCK_DIM, BLOCK_DIM, BLOCK_DIM
	};

	const std::vector<GLfloat> topFace
	{
		0,          BLOCK_DIM, BLOCK_DIM,
		BLOCK_DIM, BLOCK_DIM, BLOCK_DIM,
		BLOCK_DIM, BLOCK_DIM, 0,
		0,          BLOCK_DIM, 0
	};

	const std::vector<GLfloat> bottomFace
	{
		0,          0, 0,
		BLOCK_DIM, 0, 0,
		BLOCK_DIM, 0, BLOCK_DIM,
		0,          0, BLOCK_DIM
	};

	constexpr GLfloat TOP_LIGHT = 1.0f;
	constexpr GLfloat X_LIGHT = 0.8f;
	constexpr GLfloat Z_LIGHT = 0.6f;
	constexpr GLfloat BOTTOM_LIGHT = 0.6f;


const std::vector<GLfloat> textureCoords =
{
	1.0f, 1.0f,
	0.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f
};

Vector3 arrayIndexOneToThreeDim(int i) {
	Vector3 arrayCoords;
	arrayCoords.x = i % CHUNK_SIZE_X;
	arrayCoords.y = (i / CHUNK_SIZE_X) % CHUNK_SIZE_Y;
	arrayCoords.z = i / (CHUNK_SIZE_X * CHUNK_SIZE_Y);
	return arrayCoords;
}


Chunk::Chunk(const IntVector3 positon)
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

	//auto& atlas = Block::Database::get().textures;


	for (int x = 0; x < CHUNK_SIZE_X; ++x)
	{
		for (int y = 0; y < CHUNK_SIZE_Y; ++y)
		{
			for (int z = 0; z < CHUNK_SIZE_Z; ++z)
			{
				if (m_blocks.get(x, y, z) != static_cast<uint8_t>(Block::ID::Air)) {
					IntVector3 blockPosition(x, y, z);

					// 0 is air
					if (!isBlockHere(IntVector3(x, y + 1, z))) 
					{
						mesh.addFace(topFace,
									 textureCoords,
									 1.0f,
									 blockPosition);
					}

					if (!isBlockHere(IntVector3(x, y - 1, z))) 
					{
						mesh.addFace(bottomFace,
									 textureCoords,
									 3.0f,
								 	 blockPosition);
					}

					if (!isBlockHere(IntVector3(x + 1, y, z))) 
					{
						mesh.addFace(rightFace,
									 textureCoords,
									 2.0f,
									 blockPosition);
					}

					if (!isBlockHere(IntVector3(x - 1, y, z))) 
					{
						mesh.addFace(leftFace,
									 textureCoords,
									 2.0f,
									 blockPosition);
					}

					if (!isBlockHere(IntVector3(x, y, z + 1))) 
					{
						mesh.addFace(frontFace,
									 textureCoords,
									 2.0f,
									 blockPosition);
					}

					if (!isBlockHere(IntVector3(x, y, z - 1))) 
					{
						mesh.addFace(backFace,
									 textureCoords,
									 2.0f,
									 blockPosition);
					}
				}
			}
		}
	}

	mesh.buffer();

	changed = false;
}

const Mesh& Chunk::getMesh() const
{
	return mesh;
}

const IntVector3& Chunk::getPosition() const
{
	return m_position;
}

void Chunk::setPosition(const IntVector3& position)
{
	m_position = position;
}

const Block_Array* Chunk::getBlockArray() const
{
	return &m_blocks;
}

void Chunk::setBlock(uint32_t x, uint32_t y, uint32_t z, uint8_t value)
{
	if (x == 0 && left)
		left->changed = true;
	if (x == CHUNK_SIZE_X - 1 && right)
		right->changed = true;
	if (y == 0 && below)
		below->changed = true;
	if (y == CHUNK_SIZE_Y - 1 && above)
		above->changed = true;
	if (z == 0 && front)
		front->changed = true;
	if (z == CHUNK_SIZE_Z - 1 && back)
		back->changed = true;

	m_blocks.set(x, y, z, value);
	changed = true;
}

uint8_t Chunk::getBlock(uint32_t x, uint32_t y, uint32_t z) const
{
	return m_blocks.get(x, y, z);
}

void Chunk::setChanged(bool value)
{
	changed = value;
}

void Chunk::checkForRebuild()
{
	if (changed) generate();
}

bool Chunk::isBlockHere(IntVector3 position, bool edgesIncluded) const
{

	// if out of range of our chunk
	if (position.x < 0) {
		if (left != nullptr) {
			//std::cout << "X: " << ((int)position.x + CHUNK_SIZE) << "Y: " << (int)position.y << "Z: " << (int)position.z << std::endl;
			//std::cout << left->changed << std::endl;
			return left ? left->getBlockArray()->exists(position.x + CHUNK_SIZE_X, position.y, position.z) : 0;
		}
		return false;
	}
	if (position.x >= CHUNK_SIZE_X) {
		if (right != nullptr) {
			return right ? right->getBlockArray()->exists(position.x - CHUNK_SIZE_X, position.y, position.z) : 0;
		}
		return false;
	}
	if (position.y < 0) {
		if (below != nullptr) {
			return below ? below->getBlockArray()->exists(position.x, position.y + CHUNK_SIZE_Y, position.z) : 0;
		}
		return false;
	}
	if (position.y >= CHUNK_SIZE_Y) {
		if (above != nullptr) {
			return above ? above->getBlockArray()->exists(position.x, position.y - CHUNK_SIZE_Y, position.z) : 0;
		}
		return false;
	}
	if (position.z < 0) {
		if (front != nullptr) {
			return front ? front->getBlockArray()->exists(position.x, position.y, position.z + CHUNK_SIZE_Z) : 0;
		}
		return false;
	}
	if (position.z >= CHUNK_SIZE_Z) {
		if (back != nullptr) {
			return back ? back->getBlockArray()->exists(position.x, position.y, position.z - CHUNK_SIZE_Z) : 0;
		}
		return false;
	}
	return m_blocks.exists(position.x, position.y, position.z);

}

