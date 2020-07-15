#pragma once
#include "../Model.h"
#include "../Texture/Texture.h"
#include "../Display.h"

#include <vector>

class Crosshair
{
public:
	Crosshair();
	const Model& getModel() const;
	const Texture::Basic_Texture& getTexture() const;

private:
	Model m_model;
	Texture::Basic_Texture m_texture;
};