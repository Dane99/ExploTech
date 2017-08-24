#include "Text_Manager.h"
#include <iostream>

Text_Manager::Text_Manager()
{
}

Text_Manager::~Text_Manager()
{
}

Text_Manager& Text_Manager::get()
{
	static Text_Manager textManager;
	return textManager;
}

unsigned int Text_Manager::addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color)
{
	m_textData[currentID] = TextData(text, x, y, sx, sy);
	m_textData[currentID].textModel = std::make_unique<TextModel>();
	m_textData[currentID].textModel->createText(text.c_str(), x, y, sx, sy);
	m_textData[currentID].color = color;


	return currentID++;
}

void Text_Manager::setTextContent(const std::string& text, unsigned int id)
{

	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.text = text;
		it->second.changed = true;
	}
}

void Text_Manager::setTextPositionX(float x, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.x = x;
		it->second.changed = true;
	}
}

void Text_Manager::setTextPositionY(float y, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.y = y;
		it->second.changed = true;
	}
}

void Text_Manager::changeTextPositionX(float x, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.x += x;
		it->second.changed = true;
	}
}

void Text_Manager::changeTextPositionY(float y, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.y += y;
		//std::cout << "ID: " << id << std::endl;
		//std::cout << "TextManager: " << it->second.y << std::endl;
		it->second.changed = true;
	}
}

void Text_Manager::setScaleX(float sx, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.sx = sx;
		it->second.changed = true;
	}
}

void Text_Manager::setScaleY(float sy, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.sy = sy;
		it->second.changed = true;
	}
}

void Text_Manager::setColor(const Vector3& color, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		// This does not need to set changed to true because color is updated every cycle in the text renderer.
		it->second.color = color;
	}
}

std::string Text_Manager::getTextString(unsigned int id) const
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		return it->second.text;
	}
	return "NULL";
}

float Text_Manager::getTextPositionX(unsigned int id) const
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		return it->second.x;
	}
	std::cout << "Error getting text position x." << std::endl;
}

float Text_Manager::getTextPositionY(unsigned int id) const
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		return it->second.y;
	}
	std::cout << "Error getting text position y." << std::endl;
}

float Text_Manager::getTextScaleX(unsigned int id) const
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		return it->second.sx;
	}
	std::cout << "Error getting scale x." << std::endl;
}

float Text_Manager::getTextScaleY(unsigned int id) const
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		return it->second.sy;
	}
	std::cout << "Error getting scale y." << std::endl;
}

Vector3 Text_Manager::getTextColor(unsigned int id) const
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		return it->second.color;
	}
	std::cout << "Error getting scale y." << std::endl;
}

void Text_Manager::concatenateText(const std::string& newText, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.text = it->second.text + newText;
		it->second.changed = true;
	}
}

void Text_Manager::backSpace(unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		if (it->second.text.length() > 0)
		{
			it->second.text.pop_back();
			it->second.changed = true;
		}
	}
}

void Text_Manager::deleteText(unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		//it->second.textModel.reset();
		m_textData.erase(it);
	}

}

std::map<unsigned int, TextData, textCompare>& Text_Manager::getTextData()
{
	return m_textData;
}

void Text_Manager::recreate(unsigned int id)
{
	m_textData[id].textModel->createText(m_textData[id].text.c_str(),
		m_textData[id].x,
		m_textData[id].y,
		m_textData[id].sx,
		m_textData[id].sy);

	m_textData[id].changed = false;
}

bool Text_Manager::inRange(unsigned int id)
{
	if (id < m_textData.size())
	{
		return true;
	}
	else
	{
		std::cout << "ERROR: changeText id out of range!" << '\n';
		return false;
	}
}
