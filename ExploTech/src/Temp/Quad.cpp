#include "Quad.h"

#include <vector>

#include "../Texture/Texture_Atlas.h"

namespace
{
	const std::vector<GLfloat> vertexPositions =
	{
		//Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		//Right-Side
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		//Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		//Left
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		//Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		//Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	const std::vector<GLuint> indices =
	{
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	const std::vector<GLfloat> layers =
	{
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};
	
	const std::vector<GLfloat> textureCoords =
	{
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};


}
Quad::Quad()
{

	//insertTextureCoords(textureAtlas.getTextureCoords({ 1, 0 }));
	//insertTextureCoords(textureAtlas.getTextureCoords({ 1, 0 }));
	//insertTextureCoords(textureAtlas.getTextureCoords({ 1, 0 }));
	//insertTextureCoords(textureAtlas.getTextureCoords({ 1, 0 }));
	//insertTextureCoords(textureAtlas.getTextureCoords({ 0, 0 }));
	//insertTextureCoords(textureAtlas.getTextureCoords({ 2, 0 }));

	m_model.addData(vertexPositions, textureCoords, layers, indices);
}

Quad::Quad(Vector3 worldPosition)
{
	position = worldPosition;
	m_model.addData(vertexPositions, textureCoords, layers, indices);
}

const Model& Quad::getModel() const
{
	return m_model;
}
