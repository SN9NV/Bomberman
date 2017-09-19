//
// Created by Owen Exall on 2017/08/16.
//

#include <glm/gtc/matrix_transform.hpp>
#include "TextRenderer.hpp"
#include "../error_handling/Exceptions.hpp"

cge::TextRenderer::TextRenderer() :
	_textShader("../shaders/text.v.glsl", "../shaders/text.f.glsl")
{
	if (FT_Init_FreeType(&this->_ft)) {
		std::cout << "Failed to init FreeType." << std::endl;
		throw BombermanException("Failed to init FreeType.");
	}
	std::cout << "Initialized FreeType." << std::endl;

	if (FT_New_Face(this->_ft, "../resources/Fonts/DroidSerif-Regular.ttf", 0, &this->_face)) {
		std::cout << "Could not open font." << std::endl;
		throw BombermanException("Could not open font.");
	}
	std::cout << "Initialized New face." << std::endl;


	this->_textShader.begin();
	_attribute_coord = this->_textShader.getAttributeLocation("coord");
	_uniform_tex = this->_textShader.getUniformLocation("tex");
	_uniform_color = this->_textShader.getUniformLocation("textColor");
	_uniform_project = this->_textShader.getUniformLocation("project");
	this->_textShader.end();

	if(_attribute_coord == -1 || _uniform_tex == -1 || _uniform_color == -1) {
		std::cout << "Failed to get Uniform Location of attribute_coord/text/color." << std::endl;
		throw BombermanException("Failed to get Uniform Location of attribute_coord/text/color.");
	}
	FT_Set_Pixel_Sizes(_face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (int i = 0; i < 128; ++i) {
		if (FT_Load_Char(_face, i, FT_LOAD_RENDER) != 0)
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				_face->glyph->bitmap.width,
				_face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				_face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		t_char character = {
				texture,
				glm::ivec2(_face->glyph->bitmap.width, _face->glyph->bitmap.rows),
				glm::ivec2(_face->glyph->bitmap_left, _face->glyph->bitmap_top),
				(GLuint)(_face->glyph->advance.x)
		};
		charMap.insert(std::pair<GLchar, t_char>(i, character));
	}
	FT_Done_Face(_face);
	FT_Done_FreeType(_ft);
	// Create the vertex buffer object
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

cge::TextRenderer::~TextRenderer() {
	//glDeleteVertexArrays();
}

void cge::TextRenderer::DrawText(std::string text, float x, float y, glm::vec3 color, float scale, float screenWidth, float screenHight) {

	glm::mat4 projection = glm::ortho(0.0f, screenWidth, 0.0f, screenHight);

	this->_textShader.begin();
	_textShader.uploadvec3d(_uniform_color, color);
	_textShader.uploadMatrix4f(_uniform_project, projection);
	// Enable blending, necessary for our alpha texture
	glEnable(GL_BLEND);
	//glDisable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	for (auto &c : text)
	{
		t_char ch = charMap[c];

		GLfloat xpos = x + ch.bering.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bering.y) * scale;

		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->_textShader.end();
}
