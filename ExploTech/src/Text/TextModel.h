#pragma once
#include "GL/glew.h"

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include "../Glm_Common.h"
#include <ft2build.h>
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

class TextModel
{
public:
	TextModel();

	~TextModel();

	void bind() const;
	void unbind() const;

	void createText(const char *text, float x, float y, float sx, float sy);

	GLuint getVerticesCount() const;

	void setColor(const Vector3& color);
	Vector3 getColor() const;

private:

	int atlasWidth = 0;
	int atlasHeight = 0;

	int numberOfCharactersToDraw = 0;

	GLuint m_vao = 0, m_vbo = 0;
	GLuint m_textureID = 0;

	Vector3 m_color;
};