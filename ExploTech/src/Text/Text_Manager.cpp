#include "Text_Manager.h"

Text_Manager::Text_Manager()
{
}

Text_Manager::~Text_Manager()
{
}

unsigned int Text_Manager::addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color)
{
	m_textData[currentID] = TextData(text, x, y, sx, sy);
	m_textData[currentID].textModel = std::make_unique<TextModel>();
	m_textData[currentID].textModel->createText(text.c_str(), x, y, sx, sy);
	m_textData[currentID].color = color;


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
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		// This does not need to set changed to true because color is updated every cycle in the text renderer.
		it->second.color = color;
	}
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
		std::cout << "BEFORE: " << it->second.text << '\n';
		it->second.text.pop_back();
		std::cout << "AFTER: " << it->second.text << '\n';
		it->second.changed = true;
	}
}

void Text_Manager::deleteText(unsigned int id)
{
	auto it = m_textData.find(id);
	if (it != m_textData.end())
	{
		m_textData.erase(it);
		//it->second.textModel.release();
	}

}

std::map<unsigned int, TextData>& Text_Manager::getTextData()
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

	//m_textData[id].changed = false;
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
