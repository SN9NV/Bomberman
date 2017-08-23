//
// Created by Owen Exall on 2017/08/16.
//

#include <glm/gtc/matrix_transform.hpp>
#include "SpriteRenderer.hpp"
#include "../entites/Sprite.hpp"

cge::SpriteRenderer::SpriteRenderer() : _shader("shaders/sprite.v.glsl", "shaders/sprite.f.glsl") {
//	_uniform_tex = this->_shader.getUniformLocation("tex");
	this->_shader.begin();
	_uniform_project = this->_shader.getUniformLocation("project");
	this->_shader.end();
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

void cge::SpriteRenderer::DrawSprite(Sprite &sprite, float screenWidth, float screenHight) {
	glm::mat4 projection = glm::ortho(0.0f, screenWidth, 0.0f, screenHight);
	float scale = sprite.getScale();
	this->_shader.begin();
	_shader.uploadMatrix4f(_uniform_project, projection);
	// Enable blending, necessary for our alpha texture
	glEnable(GL_BLEND);
	//glDisable(GL_DEPTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	GLfloat xpos = sprite.getPosition().x;
	GLfloat ypos = sprite.getPosition().y;
	GLfloat w = sprite.getSize().x * scale;
	GLfloat h = sprite.getSize().y * scale;
	// Update VBO for each character
	GLfloat vertices[6][4] = {
			{xpos,     ypos + h, 0.0, 0.0},
			{xpos,     ypos,     0.0, 1.0},
			{xpos + w, ypos,     1.0, 1.0},

			{xpos,     ypos + h, 0.0, 0.0},
			{xpos + w, ypos,     1.0, 1.0},
			{xpos + w, ypos + h, 1.0, 0.0}
	};
	// Render glyph texture over quad
	glBindTexture(GL_TEXTURE_2D, sprite.getTexture().getID());
	// Update content of VBO memory
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Render quad
	glDrawArrays(GL_TRIANGLES, 0, 6);
	// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
	glDisable(GL_BLEND);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	this->_shader.end();
}
