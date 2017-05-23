#pragma once
#include "../Text/Text_Manager.h"
#include "../Shaders/Text_Shader.h"
#include "../Display.h"
#include "../Glm_Common.h"

namespace Renderer
{
	class Text_Renderer
	{
	public:

		void addToTextRenderList(Text_Manager& textManager);

		void update();

	private:

		Shader::Text_Shader m_shader;
		Text_Manager* m_textManager;
	};
}