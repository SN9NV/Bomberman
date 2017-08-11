//
// Created by rojones on 2017/08/08.
//

#include "Bomb.hpp"

Bomb::Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, int _bombradius)
		: Entity(position, rotation, scale, model), _bombradius(_bombradius), _ticks(1000) {}

Bomb::Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox, int _bombradius)
		: Entity(position, rotation, scale, model, hitBox), _bombradius(_bombradius), _ticks(1000) {}


void Bomb::update(const cge::InputManager &input, unsigned lastFrameTime) {
	_ticks -= lastFrameTime;
	(void)input;
}

bool Bomb::isDeternate()
{
	return (_ticks <= 0);
}

int Bomb::getBombradius() const
{
	return _bombradius;
}

