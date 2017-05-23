#include "Text_Manager.h"

Text_Manager::Text_Manager()
{
}

Text_Manager::~Text_Manager()
{
}

void Text_Manager::addText(const std::string& text, float x, float y, float sx, float sy)
{
	m_textModels.push_back(std::make_unique<TextModel>());
	m_textModels.back().get()->createText(text.c_str(), x, y, sx, sy);
}

void Text_Manager::changeText(const std::string& text, unsigned int id)
{
	if (inRange(id))
	{
		m_textModels[id]->createText(text.c_str(),
									 m_textModels[id]->getPositionX(),
									 m_textModels[id]->getPositionY(),
								     m_textModels[id]->getScaleX(),
									 m_textModels[id]->getScaleY());
	}
}

void Text_Manager::changeText(const std::string& text, unsigned int id, float sx, float sy)
{
	if (inRange(id))
	{
		m_textModels[id]->createText(text.c_str(),
									 m_textModels[id]->getPositionX(),
									 m_textModels[id]->getPositionY(),
									 sx,
									 sy);
	}
}

void Text_Manager::changeText(const std::string& text, unsigned int id, float x, float y, float sx, float sy)
{
	if (inRange(id))
	{
		m_textModels[id]->createText(text.c_str(),
									 x,
									 y,
									 sx,
									 sy);
	}
}

std::vector<std::unique_ptr<TextModel>>* Text_Manager::getTextElements()
{
	return &m_textModels;
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
