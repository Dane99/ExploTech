#include "Mesh.h"

#include "../WorldConstants.h"

void Mesh::reset()
{
	m_indicesIndex = 0;
	m_facesCount = 0;
}

void Mesh::addFace( const std::vector<GLfloat>&    templateFace,
					const std::vector<GLfloat>&    texCoords,
					const PositionTypes::Large_Position& chunkPos,
					const PositionTypes::Small_Position& blockPos)
{
	++m_facesCount;

	for (int i = 0, index = 0; i < 4; ++i)
	{
		m_verticies.push_back(templateFace[index++] + chunkPos.x * CHUNK_SIZE + blockPos.x);
		m_verticies.push_back(templateFace[index++] + chunkPos.y * CHUNK_SIZE + blockPos.y);
		m_verticies.push_back(templateFace[index++] + chunkPos.z * CHUNK_SIZE + blockPos.z);
	}

	m_texCoords.insert(m_texCoords.end(), texCoords.begin(), texCoords.end());

	m_indices.insert(m_indices.end(),
	{
		m_indicesIndex,
		m_indicesIndex + 1,
		m_indicesIndex + 2,
		m_indicesIndex + 2,
		m_indicesIndex + 3,
		m_indicesIndex
	});
	m_indicesIndex += 4;
}

void Mesh::buffer()
{
	m_model.addData(m_verticies, m_texCoords, m_indices);

	m_verticies.clear();
	m_texCoords.clear();
	m_indices.clear();

	m_verticies.shrink_to_fit();
	m_texCoords.shrink_to_fit();
	m_indices.shrink_to_fit();
}
