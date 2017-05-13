#pragma once

#include <string>
#include "Block_ID.h"
#include "../../Glm_Common.h"

namespace Block
{

	struct Block_Data
	{
		Block_Data() = default;
		Block_Data(Block_Data& other) = delete;

		ID          blockID;
		std::string name;
		bool        isOpaque = true;
		//bool        isObstacle = true;
		Vector2     topTextureCoords;
		Vector2     sideTextureCoords;
		Vector2     bottomTextureCoords;
	};

	class Data
	{
		public:
			Data(const std::string fileName);

			const Block_Data& getBlockData() const { return m_holder; }

		private:
			Block_Data m_holder;;
	};
}