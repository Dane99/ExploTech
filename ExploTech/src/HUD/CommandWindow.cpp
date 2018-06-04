#include "CommandWindow.h"

namespace {

	const float WIDTH = Display::WIDTH;
	const float HEIGHT = Display::HEIGHT;

	float horizontalBuffer = 0.01f * WIDTH;
	float verticalBuffer = 10.0f;
	float HeightDelta = 24.0f;

	std::vector<GLfloat> vertices =
	{
		WIDTH - horizontalBuffer,  HeightDelta + verticalBuffer, 0.0f,  // Top Right
		WIDTH - horizontalBuffer,  verticalBuffer			   , 0.0f,  // Bottom Right

		horizontalBuffer,  verticalBuffer, 0.0f,  // Bottom Left
		horizontalBuffer,  HeightDelta + verticalBuffer, 0.0f   // Top Left 

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

CommandWindow::CommandWindow()
{
	model.addData(vertices, texCoords, indices);
	texture.load("CommandWindow");
}

const Model& CommandWindow::getModel() const
{
	return model;
}

const Texture::Basic_Texture& CommandWindow::getTexture() const
{
	return texture;
}
