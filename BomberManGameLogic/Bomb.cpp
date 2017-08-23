//
// Created by rojones on 2017/08/08.
//

#include "Bomb.hpp"

Bomb::Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, int bombRadius, float hitBox) :
		Entity(position, rotation, scale, model, loader, hitBox), _bombRadius(bombRadius), _ticks(1000)
{
	this->_setEffects();
}


bool Bomb::update(const cge::InputManager &input, unsigned lastFrameTime) {
	_ticks -= lastFrameTime;
	(void)input;
	return (_ticks > 0);
}

bool Bomb::isDeternate()
{
	return (_ticks <= 0);
}

int Bomb::getBombradius() const
{
	return _bombRadius;
}

Bomb::~Bomb()
{
	this->playEffect("explosion");
}

void Bomb::_setEffects() {
	this->addNewSoundEffect("explosion", "resources/audio/boom.wav");
}

