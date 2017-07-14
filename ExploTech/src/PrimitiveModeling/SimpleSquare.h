#pragma once
#include <string>

#include "../Model.h"
#include "../Texture/Texture.h"
#include "../Display.h"

#include <vector>

class SimpleSquare
{
public:
	SimpleSquare(int sizeX, int sizeY, std::string textureName);

	void getSizeX() const;
	void getSizeY() const;


private:
	int m_sizeX;
	int m_sizeY;

	Model model;
	Texture::Basic_Texture texture;
};