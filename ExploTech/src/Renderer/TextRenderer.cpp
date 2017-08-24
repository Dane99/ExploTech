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
		}

		m_shader.setColorVector(textData.second.color);

		textData.second.textModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, textData.second.textModel->getVerticesCount());
		textData.second.textModel->unbind();
	}

	m_textManager = nullptr;
}
