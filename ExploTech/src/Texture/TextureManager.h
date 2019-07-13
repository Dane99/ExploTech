#pragma once
#include "TextureArray2D.h"
#include "../World/Block/Block_ID.h"

class TextureManager
{
public:
	static TextureManager& get();
	TextureManager();
	TextureArray2D* getPtrTextureArray();

private:
	TextureArray2D m_blockTexture;
};