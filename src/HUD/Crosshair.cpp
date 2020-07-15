#include "Crosshair.h"

namespace{

	constexpr float CROSSHAIR_SIZE = 15.0f;
	const float WIDTH = Display::WIDTH;
	const float HEIGHT = Display::HEIGHT;

	std::vector<GLfloat> vertices = 
	{
		 WIDTH / 2 + CROSSHAIR_SIZE,  HEIGHT / 2 + CROSSHAIR_SIZE, 0.0f,  // Top Right
		 WIDTH / 2 + CROSSHAIR_SIZE,  HEIGHT / 2 - CROSSHAIR_SIZE, 0.0f,  // Bottom Right

		 WIDTH / 2 - CROSSHAIR_SIZE,  HEIGHT / 2 - CROSSHAIR_SIZE, 0.0f,  // Bottom Left
		 WIDTH / 2 - CROSSHAIR_SIZE,  HEIGHT / 2 + CROSSHAIR_SIZE, 0.0f   // Top Left 

	};

	std::vector<GLfloat> texCoords =
	{
		1.0f, 1.0f,   // Top Right
		1.0f, 0.0f,   // Bottom Right

		0.0f, 0.0f,   // Bottom Left
		0.0f, 1.0f,    // Top Left 
	};

	std::vector<GLuint> indices =
	{
		0, 1, 3,   // First Triangle
		1, 2, 3    // Second Triangle
	};
}

Crosshair::Crosshair()
{
	m_model.addData(vertices, texCoords, indices);
	m_texture.load("Crosshair");
}

const Model& Crosshair::getModel() const
{
	return m_model;
}

const Texture::Basic_Texture& Crosshair::getTexture() const
{
	return m_texture;
}
