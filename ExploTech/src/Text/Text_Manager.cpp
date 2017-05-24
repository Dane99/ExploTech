#include "Text_Manager.h"

Text_Manager::Text_Manager()
{
}

Text_Manager::~Text_Manager()
{
}

unsigned int Text_Manager::addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color)
{
	m_textModels[currentID] = std::make_unique<TextModel>();
	m_textModels[currentID]->createText(text.c_str(), x, y, sx, sy);
	m_textModels[currentID]->setColor(color);

	m_textData[currentID] = TextData(text, x, y, sx, sy);

	return currentID++;
}

void Text_Manager::changeTextContent(const std::string& text, unsigned int id)
{

	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.text = text;
		it->second.changed = true;
	}
}

void Text_Manager::changeTextPositionX(float x, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.x = x;
		it->second.changed = true;
	}
}

void Text_Manager::changeTextPositionY(float y, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.y = y;
		it->second.changed = true;
	}
}

void Text_Manager::changeScaleX(float sx, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.sx = sx;
		it->second.changed = true;
	}
}

void Text_Manager::changeScaleY(float sy, unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		it->second.sy = sy;
		it->second.changed = true;
	}
}

void Text_Manager::changeColor(const Vector3& color, unsigned int id)
{
	auto it = m_textModels.find(id);
	if (it != m_textModels.end())
	{
		// This does not need to set changed to true because color is updated every cycle in the text renderer.
		it->second->setColor(color);
	}
}



std::map<unsigned int, std::unique_ptr<TextModel>>& Text_Manager::getTextElements()
{
	return m_textModels;
}

void Text_Manager::deleteText(unsigned int id)
{
	auto it = m_textModels.find(id);
	if (it != m_textModels.end())
	{
		it->second.reset();
		m_textModels.erase(it);
	}

	auto it2 = m_textData.find(id);
	if (it2 != m_textData.end())
	{
		m_textData.erase(it2);
	}

}

std::map<unsigned int, TextData>& Text_Manager::getTextData()
{
	return m_textData;
}

void Text_Manager::recreate(unsigned int id)
{
	m_textModels[id]->createText(m_textData[id].text.c_str(),
		m_textData[id].x,
		m_textData[id].y,
		m_textData[id].sx,
		m_textData[id].sy);

	//m_textData[id].changed = false;
}

bool Text_Manager::inRange(unsigned int id)
{
	if (id < m_textModels.size())
	{
		return true;
	}
	else
	{
		std::cout << "ERROR: changeText id out of range!" << '\n';
		return false;
	}
}
