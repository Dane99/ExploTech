#pragma once
#include "GL/glew.h"

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include "../Glm_Common.h"
#include "ft2build.h"
#include "freetype/ftglyph.h"
#include FT_FREETYPE_H

namespace
{

	struct character_info {
		float ax; // advance.x
		float ay; // advance.y

		float bw; // bitmap.width;
		float bh; // bitmap.rows;

		float bl; // bitmap_left;
		float bt; // bitmap_top;

		float tx; // x offset of glyph in texture coordinates
	} characters[128];

	struct point {
		point(GLfloat x,
			GLfloat y,
			GLfloat s,
			GLfloat t)
			:x(x)
			, y(y)
			, s(s)
			, t(t)
		{

		}

		GLfloat x;
		GLfloat y;
		GLfloat s;
		GLfloat t;
	};
}

class Sentence
{
public:
	Sentence();

	~Sentence();

	void bind() const;
	void unbind() const;

	void createText(const char *text, float x, float y, float sx, float sy);

	GLuint getVerticesCount() const;

private:

	int m_atlasWidth = 0;
	int m_atlasHeight = 0;

	int m_numberOfCharactersToDraw = 0;

	GLuint m_vao = 0;
	GLuint m_vbo = 0;
	GLuint m_textureID = 0;

	GLuint m_fontPadding = 1;
};