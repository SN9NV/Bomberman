//
// Created by Robert JONES on 2017/08/23.
//

#include "Sprite.hpp"

const glm::vec2 &cge::Sprite::getPosition() const {
	return _position;
}

const glm::vec2 &cge::Sprite::getSize() const {
	return _size;
}

const cge::Texture &cge::Sprite::getTexture() const {
	return _texture;
}

float cge::Sprite::getScale() const {
	return _scale;
}

cge::Sprite::Sprite(const glm::vec2 &_position, const glm::vec2 &_size, float _scale, const cge::Texture &_texture)
		: _position(_position), _size(_size), _scale(_scale), _texture(_texture) {}
