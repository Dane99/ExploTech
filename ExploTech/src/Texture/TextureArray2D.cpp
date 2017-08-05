#include "TextureArray2D.h"

TextureArray2D::TextureArray2D(const std::string& fileName, int widthOfSubtexture, int heightOfSubtexture, int layerCount)
{
	std::string filePath = "Data/Textures/" + fileName + ".png";

	sf::Image image;
	image.loadFromFile(filePath);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID);
	//Allocate the storage.
	// Second parameter is the mipmap level count.
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, widthOfSubtexture, heightOfSubtexture, layerCount);
	//Upload pixel data.
	//The first 0 refers to the mipmap level (level 0, since there's only 1)
	//The following 2 zeroes refers to the x and y offsets in case you only want to specify a subrectangle.
	//The final 0 refers to the layer index offset (we start from index 0 and have 2 levels).
	//Altogether you can specify a 3D box subset of the overall texture, but only one mip level at a time.
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, widthOfSubtexture, heightOfSubtexture, layerCount, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	//Always set reasonable texture parameters
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Unbind the 2D texture.
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureArray2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureID);
}

void TextureArray2D::unbind() const
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}
