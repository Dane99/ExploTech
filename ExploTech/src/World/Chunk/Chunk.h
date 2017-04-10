#pragma once

#include <stdint.h> // uint8_t

#include "Mesh.h"
#include "../../Glm_Common.h"

#include "../WorldConstants.h"

class Chunk{
	public:
		Chunk(const Vector3 position);
		~Chunk();

		void generate();
		const Mesh& getMesh() const;
		const Vector3& getPosition() const;


	private:
		uint8_t ***m_blocks;

		Vector3 m_position;

		Mesh mesh;
};