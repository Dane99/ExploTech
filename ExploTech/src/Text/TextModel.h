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
	/// Holds all state information relevant to a character as loaded using FreeType
	struct Character {
		GLuint TextureID;   // ID handle of the glyph texture
		IntVector2 Size;    // Size of glyph
		IntVector2 Bearing;  // Offset from baseline to left/top of glyph
		GLuint Advance;    // Horizontal offset to advance to next glyph
	};

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

	const float& getPositionX() const;
	const float& getPositionY() const;
	const float& getScaleX() const;
	const float& getScaleY() const;

private:

	int atlasWidth = 0;
	int atlasHeight = 0;

	int numberOfCharactersToDraw = 0;

	float positionX = 0.0f;
	float positionY = 0.0f;
	float scaleX = 0.0f;
	float scaleY = 0.0f;

	GLuint m_vao = 0, m_vbo = 0;
	GLuint m_textureID = 0;
};