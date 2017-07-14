#pragma once

#include "GL/glew.h"

#include <SFML/Graphics/Image.hpp>

#include <string>

class TextureArray2D {

public:
	TextureArray2D(const std::string& fileName, int widthOfSubtexture, int heightOfSubtexture, int layerCount);

	void bind() const;
	void unbind() const;

private:
	GLuint textureID;

};