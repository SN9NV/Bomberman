//
// Created by Owen Exall on 2017/08/16.
//

#include <GL/glew.h>
#include "TextRenderer.hpp"
#include "../error_handling/Exceptions.hpp"

cge::TextRenderer::TextRenderer() :
	_textShader("../shaders/text.v.glsl", "../shaders/text.f.glsl")
{
	if (FT_Init_FreeType(&this->ft)) {
		std::cout << "Failed to init FreeType." << std::endl;
		throw BombermanException("Failed to init FreeType.");
	}
	std::cout << "Initialized FreeType." << std::endl;

	if (FT_New_Face(this->ft, "../resources/Fonts/DroidSerif-Regular.ttf", 0, &this->face)) {
		std::cout << "Could not open font." << std::endl;
		throw BombermanException("Could not open font.");
	}
	std::cout << "Initialized New face." << std::endl;


	this->_textShader.begin();
	attribute_coord = this->_textShader.getAttributeLocation("coord");
	uniform_tex = this->_textShader.getUniformLocation("tex");
	uniform_color = this->_textShader.getUniformLocation("textColor");
	this->_textShader.end();

	if(attribute_coord == -1 || uniform_tex == -1 || uniform_color == -1) {
		std::cout << "Failed to get Uniform Location of attribute_coord/text/color." << std::endl;
		throw BombermanException("Failed to get Uniform Location of attribute_coord/text/color.");
	}

	// Create the vertex buffer object
	glGenBuffers(1, &vbo);

}

cge::TextRenderer::~TextRenderer() {
}

void cge::TextRenderer::DrawText(std::string text, float x, float y) {

	float sx = 2.0f / 1024.0f;
	float sy = 2.0f / 720.0f;

	this->_textShader.begin();

	/* White background */
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	// Enable blending, necessary for our alpha texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat black[4] = { 0, 0, 0, 1 };

	// Set font size to 48 pixels, color to black
	FT_Set_Pixel_Sizes(face, 0, 48);
	glUniform4fv(uniform_color, 1, black);

	renderText("The Quick Brown Fox Jumps Over The Lazy Dog", -1 + 8 * sx, 1 - 50 * sy, sx, sy);

	this->_textShader.end();
}

void cge::TextRenderer::renderText(std::string text, float x, float y, float sx, float sy) {
	FT_GlyphSlot g = this->face->glyph;

	GLuint tex;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(uniform_tex, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	/* Clamping to edges is important to prevent artifacts when scaling */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/* Linear filtering usually looks best for text */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Set up the VBO for our vertex data */
	glEnableVertexAttribArray(attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);

	/* Loop through all characters */
	for (int p = 0; p < text.length(); p++) {
		/* Try to load and render the character */
		if (FT_Load_Char(this->face, FT_Get_Char_Index(face, text[p]), FT_LOAD_RENDER))
			continue;

		/* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

		/* Calculate the vertex and texture coordinates */
		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		point box[4] = {
			{x2, -y2, 0, 0},
			{x2 + w, -y2, 1, 0},
			{x2, -y2 - h, 0, 1},
			{x2 + w, -y2 - h, 1, 1},
		};

		/* Draw the character on the screen */
		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		/* Advance the cursor to the begin of the next character */
		x += (g->advance.x >> 6) * sx;
		y += (g->advance.y >> 6) * sy;
	}

	glDisableVertexAttribArray(attribute_coord);
	glDeleteTextures(1, &tex);

}
