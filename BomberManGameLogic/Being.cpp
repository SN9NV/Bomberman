//
// Created by rojones on 2017/08/07.
//

#include "Being.h"
#include <cmath>

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed) :
		Entity(position, rotation, scale, model),
		_speed(speed), _maxBomb(1), _plaseBomb(false),  _damage(2), _deathTimeout(1000), _alive(true)
{
	this->_n_moveDir = glm::vec3(0, 0, 0);
}

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox, float speed) :
		Entity(position, rotation, scale, model, hitBox),
		_speed(speed), _maxBomb(1), _plaseBomb(false), _damage(2), _deathTimeout(1000), _alive(true)
{
	this->_n_moveDir = glm::vec3(0, 0, 0);
}

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius,
			 float _speed, int _damage) : Entity(position, rotation, scale, model, hitBoxRadius), _speed(_speed),
										  _maxBomb(1), _plaseBomb(false), _damage(_damage), _deathTimeout(1000), _alive(true)
{
	this->_n_moveDir = glm::vec3(0, 0, 0);
}

bool Being::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	(void) input;
	if (_alive)
	{
		if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
			_n_moveDir = glm::normalize(_n_moveDir);
		_position = _position + ((lastFrameTime * _speed) * _n_moveDir);
		return (true);
	}
	else
	{
		if (_deathTimeout > lastFrameTime)
			_deathTimeout -= lastFrameTime;
		else
			_deathTimeout = 0;
		this->setScale( (float)_deathTimeout/1000.0f );
		return (_deathTimeout > 0);
	}
}

void Being::setDirection()
{
	float angle = (float)atan2(_n_moveDir.x, _n_moveDir.z);
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

void Being::setMoveDir(glm::vec3 newDir)
{
	_n_moveDir = newDir;
}

int Being::getDamage() const
{
	return _damage;
}

void Being::setDamage(int damage)
{
	Being::_damage = damage;
	if (_damage < 2)
		_damage = 2;
	if (_damage > 5)
		_damage = 5;
}

bool Being::isAlive() const
{
	return _alive;
}

void Being::setAlive(bool _alive)
{
	Being::_alive = _alive;
}





/*void Being::render() {
	_shader.start();
	_renderer.prepare();
	_renderer.render((cge::Entity&)this->getModel());
	_shader.end();
}*/