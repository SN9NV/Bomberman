//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_SPRITERENDERER_HPP
#define BOMBERMAN_SPRITERENDERER_HPP

#include <glm/vec2.hpp>
#include "GLSLProgram.hpp"
#include "../entites/Sprite.hpp"

namespace cge {
	class SpriteRenderer {
	public:
		SpriteRenderer();

		void DrawSprite(Sprite  &sprite, float screenWidth, float screenHight);
	private:
		GLSLProgram	_shader;
		GLint 		_uniform_project;
		GLuint		_vao;
		GLuint		_vbo;
	};
}


#endif //BOMBERMAN_SPRITERENDERER_HPP
