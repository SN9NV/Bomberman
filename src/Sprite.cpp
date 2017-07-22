#include "Sprite.hpp"

Sprite::Sprite() : _vboID(0) { }

Sprite::Sprite(float x, float y, float width, float height) :
		_vboID(0) {
	this->init(x, y, width, height);
}

Sprite::~Sprite() {
	if (this->_vboID) {
		glDeleteBuffers(1, &this->_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	this->_x = x;
	this->_y = y;
	this->_width = width;
	this->_height = height;

	glGenBuffers(1, &this->_vboID);

	Vertex	vertexData[6];

	// First Triangle
	vertexData[0].position = { x, y };
	vertexData[1].position = { x, y + height };
	vertexData[2].position = { x + width, y };
	vertexData[3].position = { x + width, y };
	vertexData[4].position = { x, y + height };
	vertexData[5].position = { x + width, y + height };

	vertexData[0].colour = { 255, 0, 0 };
	vertexData[1].colour = { 0, 255, 0 };
	vertexData[2].colour = { 0, 0, 255 };
	vertexData[3].colour = { 0, 0, 255 };
	vertexData[4].colour = { 0, 255, 0 };
	vertexData[5].colour = { 255, 0, 0 };

	glBindBuffer(GL_ARRAY_BUFFER, this->_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw(void) {
	glBindBuffer(GL_ARRAY_BUFFER, this->_vboID);

	glEnableVertexAttribArray(0);

	// Position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	// Colour attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, colour));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
