#include "../Block/Block_Database.h"
#include "../Block/Block_ID.h"
#include "../../Glm_Common.h"

class World_Generation
{
public:

	static World_Generation& get();

	World_Generation();
	~World_Generation();

	Block::ID getBlockTypeAt(int x, int y, int z);


};