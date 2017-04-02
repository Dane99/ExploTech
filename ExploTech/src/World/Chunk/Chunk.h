#pragma once

#include <stdint.h> // uint8_t

#include "Mesh.h"

class Full_Chunk{
	public:
		Full_Chunk();

		void Generate();
		const Mesh& getMesh() const;

	private:
		Mesh mesh;
};