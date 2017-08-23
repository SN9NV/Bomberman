//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_TEXTRENDERER_HPP
#define BOMBERMAN_TEXTRENDERER_HPP

#include <iostream>
#include <ft2build.h>
#include <map>
#include FT_FREETYPE_H
#include "GLSLProgram.hpp"

namespace cge {
	class TextRenderer {
	public:
		TextRenderer();
		~TextRenderer();

		void	DrawText(std::string text, float x, float y, glm::vec3 color, float scale, float screenWidth, float screenHight);
	private:
		cge::GLSLProgram	_textShader;

		struct point {
			GLfloat x;
			GLfloat y;
			GLfloat s;
			GLfloat t;
		};
		typedef struct s_char{
			GLuint textureID;
			glm::vec2 size;
			glm::vec2 bering;
			GLuint advance;
		} t_char;

		std::map<GLchar, t_char> charMap;

		FT_Library			_ft;
		FT_Face				_face;
		GLint				_attribute_coord;
		GLint				_uniform_tex;
		GLint				_uniform_color;
		GLint 				_uniform_project;
		GLuint 				_vao;
		GLuint				_vbo;
	};
};


#endif //BOMBERMAN_TEXTRENDERER_HPP
