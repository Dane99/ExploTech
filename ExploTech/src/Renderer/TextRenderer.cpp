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


	for(auto &textData : m_textManager->getTextData())
	{
		if(textData.second.changed == true)
		{
			m_textManager->recreate(textData.first);
			textData.second.changed = false;
		}
	}

	for (auto &textElement : m_textManager->getTextElements())
	{
		m_shader.setColorVector(textElement.second->getColor());

		textElement.second->bind();
		glDrawArrays(GL_TRIANGLES, 0, textElement.second->getVerticesCount());
		textElement.second->unbind();
	}

	m_textManager = nullptr;
}
