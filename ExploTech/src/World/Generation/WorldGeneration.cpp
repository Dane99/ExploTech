#include "WorldGeneration.h"
#include <iostream>

WorldGeneration::WorldGeneration()
{
	myNoise.SetNoiseType(FastNoise::Perlin);
}

WorldGeneration::~WorldGeneration()
{
}

Block::ID WorldGeneration::getBlockTypeAt(IntVector3 position)
{
	/*
	if ((((myNoise.GetNoise(position.x, position.z) + 1)/2))*64 > position.y)
	{
		return Block::ID::Grass;
	}
	else
	{
		return Block::ID::Air;
	}
	*/

	if (myNoise.GetNoise(position.x, position.y, position.z) > 0)
	{
		return Block::ID::Grass;
	}
	else
	{
		return Block::ID::Air;
	}
}
