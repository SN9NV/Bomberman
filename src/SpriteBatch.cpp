#include "SpriteBatch.hpp"

SpriteBatch::SpriteBatch() :
	_vbo(0), _vao(0)
{

}

SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::init()
{
	this->createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
{
	this->_sortType = sortType;
}

void SpriteBatch::end()
{
		this->_sortGlyphs();
}

void SpriteBatch::draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Colour &colour)
{
	Glyph	*newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;

	newGlyph->topLeft.colour = colour;
	newGlyph->topLeft.position = { destRect[0], destRect[1] + destRect[3] };
	newGlyph->topLeft.uv = { uvRect[0], uvRect[1] + uvRect[3] };

	newGlyph->bottomLeft.colour = colour;
	newGlyph->bottomLeft.position = { destRect[0], destRect[1] };
	newGlyph->bottomLeft.uv = { uvRect[0], uvRect[1]};

	newGlyph->bottomRight.colour = colour;
	newGlyph->bottomRight.position = { destRect[0] + destRect[2], destRect[1] };
	newGlyph->bottomRight.uv = { uvRect[0] + uvRect[2], uvRect[1] };

	newGlyph->topRight.colour = colour;
	newGlyph->topRight.position = { destRect[0] + destRect[2], destRect[1] + uvRect[3] };
	newGlyph->topRight.uv = { uvRect[0] + uvRect[2], uvRect[1] + uvRect[3] };

	this->_glyphs.push_back(newGlyph);
}

void SpriteBatch::createVertexArray()
{
	if (this->_vao == 0) {
		glGenVertexArrays(1, &this->_vao);
	}

	glBindVertexArray(this->_vao);

	if (!this->_vbo == 0) {
		glGenBuffers(1, &this->_vbo);
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
	// Colour attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, colour));
	// UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void* )offsetof(Vertex, uv));

	glBindVertexArray(0);
}

void SpriteBatch::_sortGlyphs()
{
	switch (this->_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(this->_glyphs.begin(), this->_glyphs.end(), [](Glyph *a, Glyph *b) { return (b->depth < b->depth); });
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(this->_glyphs.begin(), this->_glyphs.end(), [](Glyph *a, Glyph *b) { return (b->depth > b->depth); });
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(this->_glyphs.begin(), this->_glyphs.end(), [](Glyph *a, Glyph *b) { return (a->texture < b->texture); });
			break;
	}
}
