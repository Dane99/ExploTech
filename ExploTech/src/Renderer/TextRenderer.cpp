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

	// Update any changes in size, scale, or color.
	m_textManager->update();
	auto* Sentences = m_textManager->getSentences();

	int length = Sentences->getSize();

	for (int i = 0; i < length; i++) {
		DisplaySentence* p = Sentences->getPointerWithOffset(i);

		m_shader.setColorVector(p->getColor());
		p->sentence.bind();
		glDrawArrays(GL_TRIANGLES, 0, p->sentence.getVerticesCount());
		p->sentence.unbind();
	}

	m_textManager = nullptr;
}
