#include "Text_Manager.h"

Text_Manager::Text_Manager()
{
}

Text_Manager::~Text_Manager()
{
}

void Text_Manager::addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color)
{
	m_textModels.push_back(std::make_unique<TextModel>());
	m_textModels.back().get()->createText(text.c_str(), x, y, sx, sy);
	m_textModels.back().get()->setColor(color);
	m_textData.emplace_back(text, x, y, sx, sy);
}

void Text_Manager::changeTextContent(const std::string& text, unsigned int id)
{
	if (inRange(id))
	{
		m_textData[id].text = text;
		m_textData[id].changed = true;
	}
}

void Text_Manager::changeTextPositionX(float x, unsigned int id)
{
	if (inRange(id))
	{
		m_textData[id].x = x;
		m_textData[id].changed = true;
	}
}

void Text_Manager::changeTextPositionY(float y, unsigned int id)
{
	if (inRange(id))
	{
		m_textData[id].y = y;
		m_textData[id].changed = true;
	}
}

void Text_Manager::changeScaleX(float sx, unsigned int id)
{
	if (inRange(id))
	{
		m_textData[id].sx = sx;
		m_textData[id].changed = true;
	}
}

void Text_Manager::changeScaleY(float sy, unsigned int id)
{
	if (inRange(id))
	{
		m_textData[id].sy = sy;
		m_textData[id].changed = true;
	}
}

void Text_Manager::changeColor(const Vector3& color, unsigned int id)
{
	if (inRange(id))
	{
		// This does not need to set changed to true because color is updated every cycle in the text renderer.
		m_textModels[id]->setColor(color);
	}
}



std::vector<std::unique_ptr<TextModel>>& Text_Manager::getTextElements()
{
	return m_textModels;
}

void Text_Manager::deleteText(unsigned int id)
{
	if (inRange(id))
	{
		m_textModels[id].reset();
		m_textModels.erase(m_textModels.begin() + id);
	}
}

std::vector<TextData>& Text_Manager::getTextData()
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
