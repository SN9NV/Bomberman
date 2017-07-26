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

enum class GlyphSortType {
	NONE,
	FRONT_TO_BACK,
	BACK_TO_FRONT,
	TEXTURE
};

class SpriteBatch {
	public:
		SpriteBatch();
		~SpriteBatch();

		void	init();
		void	begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
		void	end();

		void	draw(const glm::vec4 &destRect, const glm::vec4 &uvRect, GLuint texture, float depth, const Colour &colour);
		void	renderBatch();

		void	createVertexArray();

	private:
		GLuint					_vbo;
		GLuint					_vao;
		std::vector<Glyph *>	_glyphs;
		GlyphSortType			_sortType;

		void	_sortGlyphs();
};

#endif // SPRITEBATCH_HPP
