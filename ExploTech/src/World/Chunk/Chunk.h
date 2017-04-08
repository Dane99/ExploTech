#pragma once

#include <stdint.h> // uint8_t

#include "Mesh.h"

class Chunk{
	public:
		Chunk();

		void Generate();
		const Mesh& getMesh() const;

	private:
		Mesh mesh;
};