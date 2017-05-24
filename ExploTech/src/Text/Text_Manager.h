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

	bool changed = false;
};

class Text_Manager
{
	public:
		Text_Manager();
		~Text_Manager();

		unsigned int addText(const std::string& text, float x, float y, float sx, float sy, Vector3& color);
		void changeTextContent(const std::string& text, unsigned int id);
		void changeTextPositionX(float x, unsigned int id);
		void changeTextPositionY(float y, unsigned int id);

		void changeScaleX(float sx, unsigned int id);
		void changeScaleY(float sy, unsigned int id);

		void changeColor(const Vector3& color, unsigned int id);


		std::map<unsigned int, std::unique_ptr<TextModel>>& getTextElements();

		void deleteText(unsigned int id);

		std::map<unsigned int, TextData>& getTextData();

		void recreate(unsigned int id);

	private:
		std::map<unsigned int, std::unique_ptr<TextModel>> m_textModels; // textModels are not individual characters. They are sentences.

		std::map<unsigned int, TextData> m_textData;

		bool inRange(unsigned int id);

		unsigned int currentID = 0;

};