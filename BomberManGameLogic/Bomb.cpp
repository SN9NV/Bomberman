//
// Created by rojones on 2017/08/08.
//

#include "Bomb.hpp"

Bomb::Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, int bombRadius, float ticks, float hitBox) :
		Entity(position, rotation, scale, model, loader, hitBox), _bombRadius(bombRadius), _ticks(ticks), _isDetonate(false)
{
	this->_setEffects();
}


bool Bomb::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) {
	(void)input;
	(void)shader;

	_ticks -= lastFrameTime;
	_isDetonate = (_isDetonate) ? true : (_ticks <= 0);
	return (!_isDetonate);
}


bool Bomb::isDeternate()
{
	return (_isDetonate);
}

int Bomb::getBombradius() const {
	return _bombRadius;
}

Bomb::~Bomb() {
	this->playEffect("explosion");
}

void Bomb::_setEffects() {
	this->addNewSoundEffect("explosion", "resources/audio/boom.wav");
}

void Bomb::setDetonate(bool _isDetonate) {
	Bomb::_isDetonate = _isDetonate;
}
