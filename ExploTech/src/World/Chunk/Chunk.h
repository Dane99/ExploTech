#pragma once

#include <stdint.h> // uint8_t

#include "Mesh.h"
#include "../../Glm_Common.h"

#include "../WorldConstants.h"
#include "../Block/Block_ID.h"

#include <set>

struct Block_Array
{
	Block_Array() {
		m_blockArray = new uint8_t[CHUNK_VOLUME];
	}
	
	~Block_Array()
	{
		delete[] m_blockArray;
	}

	uint8_t get(uint32_t x, uint32_t y, uint32_t z) const {
		return m_blockArray[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y];
	}

	void set(uint32_t x, uint32_t y, uint32_t z, uint8_t value) {
		m_blockArray[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y] = value;
	}

	// Returns true if the block is a solid.
	// False if not a solid.
	bool exists(uint32_t x, uint32_t y, uint32_t z) const
	{
		if (get(x, y, z) != static_cast<uint8_t>(Block::ID::Air)) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	private:
		uint8_t *m_blockArray;
};


class Chunk{
	public:
		Chunk(const IntVector3 position);
		~Chunk();

		void generate();
		const Mesh& getMesh() const;
		const Vector3& getPosition() const;

		// Pointers to neighbor chunks
		Chunk *left, *right, *below, *above, *front, *back = nullptr;

		const Block_Array* getBlockArray() const;

	private:
		// If solid block return 1 else 0
		// edgesIncluded is a setting whether or not the parameters might be outside/edges of the chunk.
		bool Chunk::isBlockHere(IntVector3 position, bool edgesIncluded = true) const;



		Block_Array m_blocks;

		Vector3 m_position;

		Mesh mesh;

		std::set<uint8_t> *typesOfBlocksInChunk;
};