#pragma once
#include <string>
#include "../Glm_Common.h"
#include "GL/glew.h"
#include <vector>
#include "Sentence.h"
#include <memory>
#include <iostream>
#include "../Util/PointerVector.h"

typedef int Identification;

// A display sentence is a sentance we want to display. It holds all the display features. E.g. size, color, location.
struct DisplaySentence {
	DisplaySentence()
	{
	}

	// Create a text string that will display on screen
	DisplaySentence(const std::string& text, float x, float y, float sx, float sy)
		: text(text)
		, x(x)
		, y(y)
		, sx(sx)
		, sy(sy)
	{
	}

	void setText(std::string text) {
		this->text = text;
		changed = true;
	}

	void setPositionX(float x) {
		this->x = x;
		changed = true;
	}

	void setPositionY(float y) {
		this->y = y;
		changed = true;
	}

	void setScaleX(float sx) {
		this->sx = sx;
		changed = true;
	}

	void setScaleY(float sy) {
		this->sy = sy;
		changed = true;
	}

	void setColor(const Vector3& color) {
		this->color = color;
		changed = true;
	}

	void setChanged(bool changed) {
		this->changed = changed;
	}

	float getPositionX() const { return x; }
	float getPositionY() const { return y; }
	float getScaleX() const { return sx; }
	float getScaleY() const { return sy; }
	const Vector3& getColor() const { return color; }
	const std::string &getText() const { return text; }

	bool getChanged() const { return changed; }
	

	// The abstract sentence. Not display sentence
	Sentence sentence;

private:

	std::string text; 
	float x;
	float y; 
	float sx;
	float sy;

	Vector3 color;

	// Has our sentence changed since the last render?
	bool changed = false;
};

class Text_Manager
{
	public:

		static Text_Manager& get();

		unsigned int addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color);
		void setTextContent(const std::string& text, int id);

		void setTextPositionX(float x, int id);
		void setTextPositionY(float y, int id);

		// Change text position is relative to the already existing position. Example: posX += x.
		void changeTextPositionX(float x, int id);
		void changeTextPositionY(float y, int id);

		void setScaleX(float sx, int id);
		void setScaleY(float sy, int id);

		void setColor(const Vector3& color, int id);

		std::string getTextString(int id) const;
		float getTextPositionX(int id) const;
		float getTextPositionY(int id) const;
		float getTextScaleX(int id) const;
		float getTextScaleY(int id) const;
		Vector3 getTextColor(int id) const;

		void concatenateText(const std::string& newText, int id);

		// Deletes the last character in the text string
		void backSpace(int id);

		void deleteText(int id);

		PointerVector<DisplaySentence>* getSentences();

		void update();

	private:
		Text_Manager();
		~Text_Manager();

		PointerVector<DisplaySentence> _DisplaySentences;
};