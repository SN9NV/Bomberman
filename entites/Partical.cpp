//
// Created by Robert JONES on 2017/08/14.
//

#include "Partical.hpp"
#include "../extras/Maths.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace cge {
	const float GRAVE = 0.00098;

	/*Partical::Partical()
	{}*/

	Partical::~Partical() {

	}

	Partical::Partical(const glm::vec3 &_position, const glm::vec3 &_verlocity, float _gravityeffect, float _lifrtime,
					   float _scale, TextureAtlas &texture) : _position(_position), _verlocity(_verlocity),
															  _gravityeffect(_gravityeffect),
															  _lifrtime(_lifrtime), _scale(_scale), _elapsedtime(0),
															  _texture(texture), _currOff({0, 0}), _nextOff({1, 1}),
															  _blend(1) {}

	bool Partical::update(unsigned lastFrameTime) {
		float progression;
		int index;

		_verlocity.y -= (GRAVE * _gravityeffect * lastFrameTime);
		_position += Maths::scaleVec3(_scale, _verlocity);
		_elapsedtime += lastFrameTime;

		progression = _elapsedtime / _lifrtime * _texture.getStages();
		_blend = static_cast<float>(fmod(progression, 1));
		index = (int) floor(progression);
		float row = index / _texture.getRow();
		float col = index % _texture.getRow();
		_currOff = {row / (float) _texture.getRow(), col / (float) _texture.getRow()};
		index = (index < _texture.getStages() - 1) ? index + 1 : index;
		row = index / _texture.getRow();
		col = index % _texture.getRow();
		_nextOff = {row / (float) _texture.getRow(), col / (float) _texture.getRow()};
		return (_elapsedtime < _lifrtime);
	}

	const glm::vec3 &Partical::getPosition() const {
		return _position;
	}

	float Partical::getScale() const {
		return _scale;
	}

	const TextureAtlas &Partical::getTexture() const {
		return _texture;
	}

	const glm::vec2 &Partical::get_currOff() const {
		return _currOff;
	}

	const glm::vec2 &Partical::get_nextOff() const {
		return _nextOff;
	}

	float Partical::get_blend() const {
		return _blend;
	}
}
