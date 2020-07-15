#include "BlockData.h"

#include <fstream>

namespace Block
{
	BlockData::BlockData(const std::string fileName)
	{
		std::ifstream inFile;

		inFile.open("../Data/Blocks/" + fileName + ".block");

		std::string title;

		while(std::getline(inFile, title))
		{ 
			if (title == "") continue;
			else if (title == "Name") {
				inFile >> m_name;
			}
			else if (title == "Opaque") {
				inFile >> m_isOpaque;
			}
		}
	}
	const std::string& BlockData::getName() const
	{
		return m_name;
	}
	bool BlockData::getOpaque() const
	{
		return m_isOpaque;
	}
}
