#include "../Block/Block_ID.h"
#include "../../Glm_Common.h"
#include "FastNoise/FastNoise.h"

class WorldGeneration
{
public:

	WorldGeneration();
	~WorldGeneration();

	Block::ID getBlockTypeAt(IntVector3 position);

	FastNoise myNoise;
};