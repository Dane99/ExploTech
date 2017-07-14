#pragma once
#include "TextureArray2D.h"

class BlockTextureManager
{
public:
	static BlockTextureManager& get();

	BlockTextureManager();

	TextureArray2D* getPtrTextureArray();

private:
	TextureArray2D m_blockTexture;
};