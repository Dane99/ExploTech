#include "Crosshair.h"

namespace{

	constexpr float CROSSHAIR_SIZE = 30.0f;
	const float WIDTH = Display::WIDTH;
	const float HEIGHT = Display::HEIGHT;

	std::vector<GLfloat> vertices = 
	{
		 CROSSHAIR_SIZE / WIDTH,   CROSSHAIR_SIZE / HEIGHT, 0.0f,  // Top Right
		 CROSSHAIR_SIZE / WIDTH,  -CROSSHAIR_SIZE / HEIGHT, 0.0f,  // Bottom Right

		-CROSSHAIR_SIZE / WIDTH,  -CROSSHAIR_SIZE / HEIGHT, 0.0f,  // Bottom Left
		-CROSSHAIR_SIZE / WIDTH,   CROSSHAIR_SIZE / HEIGHT, 0.0f   // Top Left 

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
	model.addData(vertices, texCoords, indices);
	texture.load("Crosshair");
}

const Model& Crosshair::getModel() const
{
	return model;
}

const Texture::Basic_Texture& Crosshair::getTexture() const
{
	return texture;
}
