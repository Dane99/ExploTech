#pragma once

#include <stdint.h> // uint8_t

#include "Mesh.h"
#include "../../Glm_Common.h"

#include "../WorldConstants.h"
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

	uint8_t get(uint32_t x, uint32_t y, uint32_t z) {
		return m_blockArray[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y];
	}

	void set(uint32_t x, uint32_t y, uint32_t z, uint8_t value) {
		m_blockArray[x + y * CHUNK_SIZE_X + z * CHUNK_SIZE_X * CHUNK_SIZE_Y] = value;
	}

	private:
		uint8_t *m_blockArray;
};


class Chunk{
	public:
		Chunk(const Vector3 position);
		~Chunk();

		void generate();
		const Mesh& getMesh() const;
		const Vector3& getPosition() const;


	private:

		// If solid block return 1 else 0
		// TODO incorporate multiple chunks
		bool getBlockExistence(int x, int y, int z);

		Block_Array m_blocks;

		Vector3 m_position;

		Mesh mesh;

		std::set<uint8_t> *typesOfBlocksInChunk;
};