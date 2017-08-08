//
// Created by rojones on 2017/08/07.
//

#include "Being.h"
#include <cmath>

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed) :
		Entity(position, rotation, scale, model),
		_speed(speed)
{
	this->_n_moveDir = glm::vec3(0, 0, 0);
}

void Being::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	if (_n_moveDir.x > 0 || _n_moveDir.z > 0)
		_n_moveDir = glm::normalize(_n_moveDir);
	_position = _position + ((lastFrameTime * _speed) * _n_moveDir);

	float angle = atan2(_n_moveDir.x, _n_moveDir.z);
	this->setRotation({0,angle, 0});
	(void) input;
}

/*void Being::render() {
	_shader.start();
	_renderer.prepare();
	_renderer.render((cge::Entity&)this->getModel());
	_shader.end();
}*/
