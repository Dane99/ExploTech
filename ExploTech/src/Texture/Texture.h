#pragma once
#include "GL/glew.h"
#include <string>

namespace Texture 
{
	class Basic_Texture
	{
		public:
			void load(const std::string& fileName);

			void bind() const;
			void unbind() const;

		private:
			GLuint m_textureID;
	};
}