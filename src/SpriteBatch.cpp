#include "SpriteBatch.hpp"
#include <iostream>


SpriteBatch::SpriteBatch() :
	_vbo(0), _vao(0)
{

}

SpriteBatch::~SpriteBatch()
{

}

void SpriteBatch::init()
{
	this->_createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
{
	this->_sortType = sortType;
	this->_renderBatches.clear();

	for(auto &glyph : this->_glyphs) {
		delete glyph;
	}

	this->_glyphs.clear();
}

void SpriteBatch::end()
{
	this->_sortGlyphs();
	this->_createRenderBatches();
}

void SpriteBatch::draw(const glm::vec4 &destRect, GLuint texture, float depth)
{
	this->draw(destRect, { 0.0f, 0.0f, 1.0f, 1.0f }, texture, depth, { 255, 255, 255, 255 });
}

void SpriteBatch::draw(const glm::vec4 &destRect, GLuint texture, float depth, const Colour &colour)
{
	this->draw(destRect, { 0.0f, 0.0f, 1.0f, 1.0f }, texture, depth, colour);
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
	newGlyph->topRight.position = { destRect[0] + destRect[2], destRect[1] + destRect[3] };
	newGlyph->topRight.uv = { uvRect[0] + uvRect[2], uvRect[1] + uvRect[3] };

	this->_glyphs.push_back(newGlyph);
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(this->_vao);

	for(auto &batch : this->_renderBatches) {
		glBindTexture(GL_TEXTURE_2D, batch.texture);
		glDrawArrays(GL_TRIANGLES, batch.offset, batch.numVerticies);
	}

	glBindVertexArray(0);
}

// Called by end
void SpriteBatch::_createRenderBatches()
{
	if (this->_glyphs.empty()) {
		return;
	}

	std::vector<Vertex>	verticies;
	verticies.resize(this->_glyphs.size() * 6);

	// cv = current vertex
	unsigned cv = 0;

	// cg = current glyph
	for(unsigned cg = 0; cg < this->_glyphs.size(); cg++) {
		// if cg == 0 because first glyph always needs to be loaded into the batch
		if (cg == 0 || this->_glyphs[cg]->texture != this->_glyphs[cg - 1]->texture) {
			this->_renderBatches.push_back(RenderBatch(cv, 6, this->_glyphs[cg]->texture));
		} else {
			this->_renderBatches.back().numVerticies += 6;
		}

		verticies[cv++] = this->_glyphs[cg]->topLeft;
		verticies[cv++] = this->_glyphs[cg]->bottomLeft;
		verticies[cv++] = this->_glyphs[cg]->bottomRight;
		verticies[cv++] = this->_glyphs[cg]->bottomRight;
		verticies[cv++] = this->_glyphs[cg]->topRight;
		verticies[cv++] = this->_glyphs[cg]->topLeft;
	}

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
	// Orphan the buffer - Faster because it's not always trying to overwrite the same memory addresses
	glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), verticies.data(), GL_DYNAMIC_DRAW);
	// Now upload the data
	//glBufferSubData(GL_ARRAY_BUFFER, 0, verticies.size() * sizeof(Vertex), verticies.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Called by init
void SpriteBatch::_createVertexArray()
{
	if (this->_vao == 0) {
		glGenVertexArrays(1, &this->_vao);
	}

	glBindVertexArray(this->_vao);

	if (this->_vbo == 0) {
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
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Called by end
void SpriteBatch::_sortGlyphs()
{
	switch (this->_sortType) {
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(this->_glyphs.begin(), this->_glyphs.end(), [](Glyph *a, Glyph *b) { return (a->depth < b->depth); });
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(this->_glyphs.begin(), this->_glyphs.end(), [](Glyph *a, Glyph *b) { return (a->depth > b->depth); });
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(this->_glyphs.begin(), this->_glyphs.end(), [](Glyph *a, Glyph *b) { return (a->texture < b->texture); });
			break;
		default:
			break;
	}
}
