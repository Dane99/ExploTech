#pragma once

#include <GL/glew.h>
#include <vector>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Model.h"
#include "PositionTypes.h"

#include "../../Glm_Common.h"

class Mesh
{
public:
	void reset();

	void Mesh::addFace(const std::vector<GLfloat>&    templateFace,
		const std::vector<GLfloat>&    texCoords,
		const Vector3& chunkPos,
		const Vector3& blockPos);

	void buffer();

	const Model& getModel() const;

	uint32_t getFaces() const;

private:
	std::vector<GLfloat> m_verticies;
	std::vector<GLfloat> m_texCoords;
	std::vector<GLuint> m_indices;

	Model m_model;

	uint32_t m_indicesIndex = 0;
	uint32_t m_facesCount = 0;
};
