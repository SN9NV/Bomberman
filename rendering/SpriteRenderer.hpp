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

		void DrawSprite(Texture &texture, glm::vec2 position,
						glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f,
						glm::vec3 color = glm::vec3(1.0f));
	private:
		GLSLProgram&	_shader;
		GLuint			_quadVAO;

		void			initRenderer();
	};
}


#endif //BOMBERMAN_SPRITERENDERER_HPP
