#pragma once

#include <string>
#include "../../Block_ID.h"
#include "../../../../Glm_Common.h"

namespace Block
{

	class BlockData
	{
		public:
			BlockData(const std::string fileName);

			const std::string& getName() const;
			bool getOpaque() const;

		private:
			std::string m_name;
			bool        m_isOpaque = true;

	};
}