#include "TextureManager.h"

TextureManager& TextureManager::get()
{
	static TextureManager textureManager;
	return textureManager;
}

TextureManager::TextureManager()
	: m_blockTexture("TextureArray", 16, 16, 4)
{
}

TextureArray2D* TextureManager::getPtrTextureArray()
{
	return &m_blockTexture;
}
