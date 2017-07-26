#ifndef SPRITEBATCH_HPP
#define SPRITEBATCH_HPP

#include <vector>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Structs.hpp"

struct Glyph {
	GLuint	texture;
	float	depth;
	Vertex	topLeft;
	Vertex	bottomLeft;
	Vertex	topRight;
	Vertex	bottomRight;
};



struct RenderBatch {
	GLuint	offset;
	GLuint	numVerticies;
	GLuint	texture;

	RenderBatch(GLuint Offset, GLuint NumVerticies, GLuint Texture) :
		offset(Offset), numVerticies(NumVerticies), texture(Texture) {}
};

class SpriteBatch {
	public:
		enum GlyphSortType {
			NONE,
			FRONT_TO_BACK,
			BACK_TO_FRONT,
			TEXTURE
		};

		SpriteBatch();
		~SpriteBatch();

		void	init();
		void	begin(GlyphSortType sortType = SpriteBatch::GlyphSortType::TEXTURE);
		void	end();

		void	draw(const glm::vec4 &destRect, GLuint texture, float depth);
		void	draw(const glm::vec4 &destRect, GLuint texture, float depth, const Colour &colour);
		void	draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Colour &colour);
		void	renderBatch();


	private:
		GLuint						_vbo;
		GLuint						_vao;
		GlyphSortType				_sortType;
		std::vector<Glyph *>		_glyphs;
		std::vector<RenderBatch>	_renderBatches;

		void	_createRenderBatches();
		void	_createVertexArray();
		void	_sortGlyphs();
};

#endif // SPRITEBATCH_HPP
