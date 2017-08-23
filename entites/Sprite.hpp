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
		glm::vec2	_position;
		glm::vec2	_size;
		float		_scale;
		Texture		_texture;
	public:
		Sprite(const glm::vec2 &_position, const glm::vec2 &_size, float _scale, const Texture &_texture);

		const glm::vec2 &getPosition() const;

		const glm::vec2 &getSize() const;

		const Texture &getTexture() const;

		float getScale() const;
	};
}

#endif //BOMBERMAN_SPRITE_HPP
