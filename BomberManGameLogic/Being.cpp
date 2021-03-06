//
// Created by rojones on 2017/08/07.
//

#include "Being.hpp"
#include "../extras/Maths.hpp"

Being::Being(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius, float speed, int damage, bool wallPass, size_t points) :
		Entity(position, rotation, scale, model, loader, hitBoxRadius),
		_speed(speed),
		_bombTime(1500),
		_maxBomb(1),
		_placeBomb(false),
		_damage(damage),
		_deathTimeout(1000),
		_alive(true),
		_wallPass(wallPass),
		_points (points)
{
	this->_n_moveDir = glm::vec3(0, 0, 0);
}

bool Being::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) {
	cge::Entity::update(input, shader, lastFrameTime);

	this->_needsTransformationUpdate = true;

	if (_alive) {
		if (_n_moveDir.x != 0 || _n_moveDir.z != 0)
			_n_moveDir = glm::normalize(_n_moveDir);
		_position += lastFrameTime * _speed * _n_moveDir;

		return true;
	}

	if (_deathTimeout > lastFrameTime)
		_deathTimeout -= lastFrameTime;
	else
		_deathTimeout = 0;

	this->setScale(_deathTimeout / 1000.0f);

	return (_deathTimeout > 0);
}

void Being::setDirection() {
	float angle = atan2f(_n_moveDir.x, _n_moveDir.z);
	cge::Entity::setRotation({0,angle, 0});
}

float Being::getDirAngle() {
	return atan2f(_n_moveDir.x, _n_moveDir.z) * 180 / static_cast<float>(M_PI);
}

const glm::vec3 &Being::get_n_moveDir() const {
	return _n_moveDir;
}
bool Being::isPlaceBomb() const {
	return _placeBomb;
}

void Being::placeBomb(Bomb *bomb) {
	_bombs.push_back(bomb);
}

bool Being::checkBombDeterNation(Bomb *bomb) {
	for (auto it = _bombs.begin(); it != _bombs.end() ; it++) {
		if (bomb == *it) {
			_bombs.erase(it);
			return true;
		}
	}
	return false;
}

void Being::setMoveDir(glm::vec3 newDir) {
	_n_moveDir = newDir;
}

int Being::getDamage() const {
	return _damage;
}

void Being::setDamage(int damage) {
	_damage = cge::Maths::clamp(damage, 2, 5);
}

bool Being::isAlive() const {
	return _alive;
}

void Being::setAlive(bool _alive) {
	if (!_alive) {
		this->playEffect("dieSound");
	}

	Being::_alive = _alive;
}

void Being::setPlaceBomb(bool placeBomb) {
	Being::_placeBomb = placeBomb;
}

void Being::setSpeed(float speed) {
	this->_speed = speed;
}

float Being::getSpeed() const {
	return (this->_speed);
}

size_t Being::getMaxBomb() const {
	return _maxBomb;
}

void Being::setMaxBomb(size_t _maxBomb) {
	Being::_maxBomb = _maxBomb;
}

bool Being::isWallPass() const {
	return _wallPass;
}

void Being::setWallPass(bool wallPass) {
	Being::_wallPass = wallPass;
}

float Being::getBombTime() const {
	return _bombTime;
}

void Being::setBombTime(float _bombTime) {
	Being::_bombTime = _bombTime;
}

size_t Being::getPoints() const {
	return _points;
}
