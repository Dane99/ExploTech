#pragma once
#include "../Model.h"
#include "../Texture/Texture.h"
#include "../Display.h"

#include <vector>

class CommandWindow
{
public:
	CommandWindow();

	const Model& getModel() const;

	const Texture::Basic_Texture& getTexture() const;

private:

	Model model;
	Texture::Basic_Texture texture;
};