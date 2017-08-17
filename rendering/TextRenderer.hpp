//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_TEXTRENDERER_HPP
#define BOMBERMAN_TEXTRENDERER_HPP

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "GLSLProgram.hpp"

namespace cge {
	class TextRenderer {
	public:
		TextRenderer();
		~TextRenderer();

		void	DrawText(std::string text, float x, float y);
	private:
		cge::GLSLProgram	_textShader;

		struct point {
			GLfloat x;
			GLfloat y;
			GLfloat s;
			GLfloat t;
		};

		FT_Library			ft;
		FT_Face				face;
		GLuint				texture;
		GLuint				attribute_coord;
		GLint				uniform_tex;
		GLint				uniform_color;
		GLuint				vbo;

		void	renderText(std::string text, float x, float y, float sx, float sy);
	};
};


#endif //BOMBERMAN_TEXTRENDERER_HPP
