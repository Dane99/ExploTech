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

	for (auto it = m_textManager->getTextElements()->begin(); it != m_textManager->getTextElements()->end(); ++it) 
	{
		//std::cout << "CALLED" << (*it)->getVerticesCount()  << '\n';
		(*it)->bind();
		//textModel->bind();
		glDrawArrays(GL_TRIANGLES, 0, (*it)->getVerticesCount());
		(*it)->unbind();
	}

	m_textManager = nullptr;
}
