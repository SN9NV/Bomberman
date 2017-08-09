//
// Created by rojones on 2017/08/07.
//

#include "Being.h"
#include <cmath>

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed) :
		Entity(position, rotation, scale, model),
		_speed(speed), _maxBomb(1), _plaseBomb(false)
{
	this->_n_moveDir = glm::vec3(0, 0, 0);
}

void Being::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
		_n_moveDir = glm::normalize(_n_moveDir);
	_position = _position + ((lastFrameTime * _speed) * _n_moveDir);
	(void) input;
}

void Being::setRotation()
{
	float angle = atan2(_n_moveDir.x, _n_moveDir.z);
	cge::Entity::setRotation({0,angle, 0});
}

float Being::getDirAngle()
{
	return (float)(atan2(_n_moveDir.x, _n_moveDir.z)*180/M_PI);
}

const glm::vec3 &Being::get_n_moveDir() const
{
	return _n_moveDir;
}
bool Being::is_placeBomb() const
{
	return _plaseBomb;
}

void Being::placeBomb(Bomb *bomb)
{
	_bombs.push_back(bomb);
}

bool Being::checkBombDeterNation(Bomb *bomb)
{
	for (std::vector<Bomb *>::iterator it = _bombs.begin(); it != _bombs.end() ; it++)
	{
		if (bomb == *it)
		{
			_bombs.erase(it);
			return (true);
		}
	}
	return false;
}



/*void Being::render() {
	_shader.start();
	_renderer.prepare();
	_renderer.render((cge::Entity&)this->getModel());
	_shader.end();
}*/
