#include "World_Generation.h"

World_Generation& World_Generation::get()
{
	static World_Generation worldGeneration;
	return worldGeneration;
}

World_Generation::World_Generation()
{
}

World_Generation::~World_Generation()
{
}

Block::ID World_Generation::getBlockTypeAt(int x, int y, int z)
{
	return Block::ID::Grass;
}
