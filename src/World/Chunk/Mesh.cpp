#include "Mesh.h"

#include "../WorldConstants.h"

#include <iostream>

Mesh::Mesh()
{
	m_vertices = std::make_unique<std::vector<GLfloat>>();
	m_texCoords = std::make_unique<std::vector<GLfloat>>();
	m_indices = std::make_unique<std::vector<GLuint>>();
	m_layers = std::make_unique<std::vector<GLfloat>>();
}

void Mesh::reset()
{
	m_indicesIndex = 0;
	m_facesCount = 0;
	m_vertices->clear();
	m_texCoords->clear();
	m_indices->clear();
	m_layers->clear();
}

void Mesh::addFace( const std::vector<GLfloat>&    templateFace,
					const std::vector<GLfloat>&    texCoords,
					const GLfloat layer,
					const Vector3& blockPos)
{
	++m_facesCount;

	// Four total vertexes needed for each side of a cube. We use an EBO or indices to substitute the two additional missing vertexes. 
	for (int i = 0, index = 0; i < 4; ++i)
	{
		// Three positions for each vertex.
		m_vertices->push_back(templateFace.at(index++) + blockPos.x);
		m_vertices->push_back(templateFace.at(index++) + blockPos.y);
		m_vertices->push_back(templateFace.at(index++) + blockPos.z);
	}

	// texCoords is appended to m_texCoords
	m_texCoords->insert(m_texCoords->end(), texCoords.begin(), texCoords.end());

	// Here is where we add the two additional vertexes.
	m_indices->insert(m_indices->end(),
	{
		m_indicesIndex,
		m_indicesIndex + 1,
		m_indicesIndex + 2,
		m_indicesIndex + 2,
		m_indicesIndex + 3,
		m_indicesIndex
	});
	m_indicesIndex += 4;

	// Layers are the texture id for the block side we are using inside the 2D texture array.
	m_layers->push_back(layer);
	m_layers->push_back(layer);
	m_layers->push_back(layer);
	m_layers->push_back(layer);



}

void Mesh::buffer()
{
	m_model.addData(*m_vertices, *m_texCoords, *m_layers, *m_indices);

	m_vertices->clear();
	m_texCoords->clear();
	m_layers->clear();
	m_indices->clear();

	m_vertices->shrink_to_fit();
	m_texCoords->shrink_to_fit();
	m_layers->shrink_to_fit();
	m_indices->shrink_to_fit();
}

const Model& Mesh::getModel() const
{
	return m_model;
}
uint32_t Mesh::getFaces() const
{
	return m_facesCount;
}
