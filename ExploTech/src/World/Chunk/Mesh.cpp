#include "Mesh.h"

#include "../WorldConstants.h"

void Mesh::reset()
{
	m_indicesIndex = 0;
	m_facesCount = 0;
}

void Mesh::addFace( const std::vector<GLfloat>&    templateFace,
					const std::vector<GLfloat>&    texCoords,
					const Vector3& chunkPos,
					const Vector3& blockPos)
{
	++m_facesCount;

	// Four total vertexes needed for each side of a cube. We use an EBO or indices to substitute two additional missing vertexes. 
	for (int i = 0, index = 0; i < 4; ++i)
	{
		// Three positions for each vertex.
		m_verticies.push_back(templateFace[index++] + chunkPos.x * (CHUNK_SIZE_X - 1) + blockPos.x);
		m_verticies.push_back(templateFace[index++] + chunkPos.y * (CHUNK_SIZE_Y - 1) + blockPos.y);
		m_verticies.push_back(templateFace[index++] + chunkPos.z * (CHUNK_SIZE_Z - 1) + blockPos.z);
	}

	// texCoords is appended to m_texCoords
	m_texCoords.insert(m_texCoords.end(), texCoords.begin(), texCoords.end());

	// Here is where we add the two 
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

const Model & Mesh::getModel() const
{
	return m_model;
}
uint32_t Mesh::getFaces() const
{
	return m_facesCount;
}
