#pragma once
#include <string>
#include "../Glm_Common.h"
#include "GL/glew.h"
#include <vector>
#include "TextModel.h"
#include <memory>
#include <iostream>

class Text_Manager
{
	public:
		Text_Manager();
		~Text_Manager();

		void addText(const std::string& text, float x, float y, float sx, float sy);
		void changeText(const std::string& text, unsigned int id);
		void changeText(const std::string& text, unsigned int id, float sx, float sy);
		void changeText(const std::string& text, unsigned int id, float x, float y, float sx, float sy);

		std::vector<std::unique_ptr<TextModel>>* getTextElements();

	private:
		std::vector<std::unique_ptr<TextModel>> m_textModels; // textModels are not individual characters. They are sentences.

		bool inRange(unsigned int id);

};