#pragma once

#include <GL/glew.h>
#include <vector>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Model.h"

class Mesh
{
public:
	void reset();

	void addMeshData(const std::vector<GLfloat>& vertices);

	void addTexCoords(const std::vector<GLfloat>& texCoords);

	void buffer();

	const Model& getModel() const
	{
		return m_model;
	}

private:
	std::vector<GLfloat> m_verticies;
	std::vector<GLfloat> m_texCoords;
	std::vector<GLuint> m_indices;

	Model m_model;

	uint32_t m_indicesIndex = 0;
};

struct Meshes
{
	Mesh solidMesh;
	Mesh liquidMesh;
};