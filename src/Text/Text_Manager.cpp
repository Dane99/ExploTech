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

	DisplaySentence* sentence = new DisplaySentence(text, x, y, sx, sy);

	int id = _DisplaySentences.push_back(sentence);

	_DisplaySentences.getLastPointer()->sentence.createText(text.c_str(), x, y, sx, sy);
	_DisplaySentences.getLastPointer()->setColor(color);

	return id;
}

void Text_Manager::setTextContent(const std::string& text, int id)
{
	_DisplaySentences.getPointerWithID(id)->setText(text);
}

void Text_Manager::setTextPositionX(float x, int id)
{
	_DisplaySentences.getPointerWithID(id)->setPositionX(x);
}

void Text_Manager::setTextPositionY(float y, int id)
{
	_DisplaySentences.getPointerWithID(id)->setPositionY(y);
}

void Text_Manager::changeTextPositionX(float x, int id)
{
	DisplaySentence* pointerToDisplaySentence = _DisplaySentences.getPointerWithID(id);
	pointerToDisplaySentence->setPositionX(pointerToDisplaySentence->getPositionX() + x);
}

void Text_Manager::changeTextPositionY(float y, int id)
{
	DisplaySentence* pointerToDisplaySentence = _DisplaySentences.getPointerWithID(id);
	pointerToDisplaySentence->setPositionY(pointerToDisplaySentence->getPositionY() + y);
}

void Text_Manager::setScaleX(float sx, int id)
{
	_DisplaySentences.getPointerWithID(id)->setScaleX(sx);
}

void Text_Manager::setScaleY(float sy, int id)
{
	_DisplaySentences.getPointerWithID(id)->setScaleY(sy);
}

void Text_Manager::setColor(const Vector3& color, int id)
{
	_DisplaySentences.getPointerWithID(id)->setColor(color);
}

std::string Text_Manager::getTextString(int id) const
{
	return _DisplaySentences.getPointerWithID(id)->getText();
}

float Text_Manager::getTextPositionX(int id) const
{
	return _DisplaySentences.getPointerWithID(id)->getPositionX();
}

float Text_Manager::getTextPositionY( int id) const
{
	return _DisplaySentences.getPointerWithID(id)->getPositionY();
}

float Text_Manager::getTextScaleX(int id) const
{
	return _DisplaySentences.getPointerWithID(id)->getScaleX();
}

float Text_Manager::getTextScaleY(int id) const
{
	return _DisplaySentences.getPointerWithID(id)->getScaleY();
}

Vector3 Text_Manager::getTextColor(int id) const
{
	return _DisplaySentences.getPointerWithID(id)->getColor();
}

void Text_Manager::concatenateText(const std::string& newText, int id)
{
	DisplaySentence* pointerToDisplaySentence = _DisplaySentences.getPointerWithID(id);
	pointerToDisplaySentence->setText(pointerToDisplaySentence->getText() + newText);
}

void Text_Manager::backSpace(int id)
{
	DisplaySentence* pointerToDisplaySentence = _DisplaySentences.getPointerWithID(id);
	std::string text = pointerToDisplaySentence->getText();

	text.pop_back();

	pointerToDisplaySentence->setText(text);
}

void Text_Manager::deleteText(int id)
{
	_DisplaySentences.eraseWithID(id);

}

PointerVector<DisplaySentence>* Text_Manager::getSentences()
{
	return &_DisplaySentences;
}

void Text_Manager::update()
{
	int length = _DisplaySentences.getSize();

	for (int i = 0; i < length; i++) {
		// Pointer to display sentence aka p.
		DisplaySentence* p = _DisplaySentences.getPointerWithOffset(i);

		if (p->getChanged() == true) {
			p->sentence.createText(p->getText().c_str(),
								   p->getPositionX(),
								   p->getPositionY(),
							  	   p->getScaleX(),
								   p->getScaleY());
		}

		p->setChanged(false);
	}
}
