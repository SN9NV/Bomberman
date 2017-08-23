//
// Created by Robert JONES on 2017/08/23.
//

#ifndef BOMBERMAN_SPRITE_HPP
#define BOMBERMAN_SPRITE_HPP


#include <glm/vec2.hpp>
#include "RawModel.hpp"
#include "Texture.hpp"

namespace cge {
	class Sprite {
	protected:
		glm::vec2 _position;
		Texture _texture;
	};
}

#endif //BOMBERMAN_SPRITE_HPP
