#pragma once

#include <string>
#include "Block_ID.h"
#include "../../Glm_Common.h"

namespace Block
{

	struct Data_Holder
	{
		Data_Holder() = default;
		Data_Holder(Data_Holder& other) = delete;

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

			const Data_Holder& getDataHolder() const { return m_holder; }

		private:
			Data_Holder m_holder;;
	};
}