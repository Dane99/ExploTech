#include "TextRenderer.h"
#include <iostream>

void Renderer::Text_Renderer::addToTextRenderList(Text_Manager& textManager)
{
	m_textManager = &textManager;
}

void Renderer::Text_Renderer::update()
{
	m_shader.bind();
	m_shader.setProjMatrix(glm::ortho(0.0f, static_cast<GLfloat>(Display::WIDTH), 0.0f, static_cast<GLfloat>(Display::HEIGHT)));

	unsigned int id = 0;

	for(auto &textData : m_textManager->getTextData())
	{
		if(textData.changed == true)
		{
			m_textManager->recreate(id);
			textData.changed = false;
		}
		++id;
	}

	for (auto &textElement : m_textManager->getTextElements())
	{
		m_shader.setColorVector(textElement->getColor());

		textElement->bind();
		glDrawArrays(GL_TRIANGLES, 0, textElement->getVerticesCount());
		textElement->unbind();
	}

	m_textManager = nullptr;
}
