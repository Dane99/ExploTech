#pragma once

#include <GL/glew.h>
#include <vector>

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Model.h"

#include "../../Glm_Common.h"

#include <memory>

class Mesh
{
public:
	Mesh();

	void reset();

	void Mesh::addFace(const std::vector<GLfloat>&    templateFace,
					   const std::vector<GLfloat>&    texCoords,
				  	   const GLfloat layer,
					   const Vector3& blockPos);

	void buffer();

	const Model& getModel() const;

	uint32_t getFaces() const;

private:
	std::unique_ptr<std::vector<GLfloat>> m_vertices;
	std::unique_ptr<std::vector<GLfloat>> m_texCoords;
	std::unique_ptr<std::vector<GLuint>> m_indices;
	std::unique_ptr<std::vector<GLfloat>> m_layers;

	Model m_model;

	uint32_t m_indicesIndex = 0;
	uint32_t m_facesCount = 0;
};
