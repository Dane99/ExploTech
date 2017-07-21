#include "TextModel.h"
#include <iostream>

TextModel::TextModel()
{
	FT_Library ft;

	if (FT_Init_FreeType(&ft)) 
	{
		fprintf(stderr, "Could not init freetype library\n");
	}

	FT_Face face;

	if (FT_New_Face(ft, "OpenSans-Regular.ttf", 0, &face)) 
	{
		fprintf(stderr, "Could not open font\n");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	FT_GlyphSlot g = face->glyph;
	int w = 0;
	int h = 0;

	for (int i = 32; i < 128; i++) {
		if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
			fprintf(stderr, "Loading character %c failed!\n", i);
			continue;
		}

		w += g->bitmap.width + m_fontPadding;
		h = std::max(h, g->bitmap.rows);
	}

	/* you might as well save this value as it is needed later on */
	atlasWidth = w;
	atlasHeight = h;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &m_textureID);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	int x = 0;

	for (int i = 32; i < 128; i++) {

		if (FT_Load_Char(face, i, FT_LOAD_RENDER))
		{
			std::cout << "Cound not load char." << '\n';
			continue;
		}
		

		// TODO CHECK THIS
		glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		x += g->bitmap.width + m_fontPadding;

		characters[i].ax = g->advance.x >> 6;
		characters[i].ay = g->advance.y >> 6;

		characters[i].bw = g->bitmap.width;
		characters[i].bh = g->bitmap.rows + m_fontPadding;

		characters[i].bl = g->bitmap_left;
		characters[i].bt = g->bitmap_top;

		characters[i].tx = (float)x;
	}

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

TextModel::~TextModel()
{
	if (m_vao != 0) 
	{
		glDeleteVertexArrays(1, &m_vao);
	}
	if (m_vbo != 0)
	{
		glDeleteBuffers(1, &m_vbo);
	}
	if (m_textureID != 0)
	{
		glDeleteTextures(1, &m_textureID);
	}
}

void TextModel::bind() const
{
	glBindVertexArray(m_vao);
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void TextModel::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void TextModel::createText(const char* text, float x, float y, float sx, float sy)
{
	std::vector<point> vertices;

	numberOfCharactersToDraw = 0;

	for (const char *p = text; *p; p++) {
		float x2 = x + characters[*p].bl * sx;
		float y2 = -y - characters[*p].bt * sy;
		float w = characters[*p].bw * sx;
		float h = characters[*p].bh * sy;

		/* Advance the cursor to the start of the next character */
		x += characters[*p].ax * sx;
		y += characters[*p].ay * sy;

		/* Skip glyphs that have no pixels */
		if (!w || !h)
			continue;

		vertices.push_back(point(x2    , -y2    , ((characters[*p - 1].tx) / atlasWidth)				   , 0                              ));
		vertices.push_back(point(x2 + w, -y2    , ( characters[*p - 1].tx + characters[*p].bw) / atlasWidth, 0                              ));
		vertices.push_back(point(x2    , -y2 - h, ((characters[*p - 1].tx) / atlasWidth)				   , characters[*p].bh / atlasHeight)); //remember: each glyph occupies a different amount of vertical space
		vertices.push_back(point(x2 + w, -y2    , ( characters[*p - 1].tx + characters[*p].bw) / atlasWidth, 0                              ));
		vertices.push_back(point(x2    , -y2 - h, ((characters[*p - 1].tx) / atlasWidth)				   , characters[*p].bh / atlasHeight));
		vertices.push_back(point(x2 + w, -y2 - h, ( characters[*p - 1].tx + characters[*p].bw) / atlasWidth, characters[*p].bh / atlasHeight));

		++numberOfCharactersToDraw;
	}

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER,  vertices.size() * sizeof(vertices[0]), vertices.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0,
						  4,
						  GL_FLOAT,
						  GL_FALSE,
						  0,
						  (GLvoid*)0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glDrawArrays(GL_TRIANGLES, 0, numberOfCharacters * 6);
}

GLuint TextModel::getVerticesCount() const
{
	return numberOfCharactersToDraw * 6; // Six vertices per character.
}