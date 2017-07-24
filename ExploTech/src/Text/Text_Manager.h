#pragma once
#include <string>
#include "../Glm_Common.h"
#include "GL/glew.h"
#include <vector>
#include "TextModel.h"
#include <memory>
#include <iostream>

struct TextData {
	TextData()
	{
	}

	TextData(const std::string& text, float x, float y, float sx, float sy)
		: text(text)
		, x(x)
		, y(y)
		, sx(sx)
		, sy(sy)
	{
	}

	std::string text; 
	float x;
	float y; 
	float sx;
	float sy;

	Vector3 color;

	std::unique_ptr<TextModel> textModel; // textModels are not individual characters. They are sentences / groups of letters.

	bool changed = false;
};

class Text_Manager
{
	public:

		static Text_Manager& get();

		unsigned int addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color);
		void setTextContent(const std::string& text, unsigned int id);

		void setTextPositionX(float x, unsigned int id);
		void setTextPositionY(float y, unsigned int id);

		// Change text position is relative to the already existing position. Example: posX += x.
		void changeTextPositionX(float x, unsigned int id);
		void changeTextPositionY(float y, unsigned int id);

		void setScaleX(float sx, unsigned int id);
		void setScaleY(float sy, unsigned int id);

		void setColor(const Vector3& color, unsigned int id);

		std::string getTextString(unsigned int id) const;
		float getTextPositionX(unsigned int id) const;
		float getTextPositionY(unsigned int id) const;
		float getTextScaleX(unsigned int id) const;
		float getTextScaleY(unsigned int id) const;
		Vector3 getTextColor(unsigned int id) const;

		void concatenateText(const std::string& newText, unsigned int id);

		// Deletes the last character in the text string
		void backSpace(unsigned int id);

		void deleteText(unsigned int id);

		std::map<unsigned int, TextData>& getTextData();

		void recreate(unsigned int id);

	private:
		Text_Manager();
		~Text_Manager();

		std::map<unsigned int, TextData> m_textData;

		bool inRange(unsigned int id);

		unsigned int currentID = 0;

};