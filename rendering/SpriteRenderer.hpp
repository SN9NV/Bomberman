//
// Created by Owen Exall on 2017/08/16.
//

#ifndef BOMBERMAN_SPRITERENDERER_HPP
#define BOMBERMAN_SPRITERENDERER_HPP

#include <glm/vec2.hpp>
#include "GLSLProgram.hpp"

namespace cge {
	class SpriteRenderer {
	public:
		SpriteRenderer(GLSLProgram &shader);

		~SpriteRenderer();

		void DrawSprite();
	private:
		GLSLProgram&	_shader;


		void			initRenderer();
	};
}


#endif //BOMBERMAN_SPRITERENDERER_HPP
