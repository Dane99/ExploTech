#include "BlockTextureManager.h"

BlockTextureManager& BlockTextureManager::get()
{
	static BlockTextureManager textureManager;
	return textureManager;
}

BlockTextureManager::BlockTextureManager()
{
	m_blockTexture.addData("TextureArray", 16, 16, 4);
}

TextureArray2D* BlockTextureManager::getPtrTextureArray()
{
	return &m_blockTexture;
}
