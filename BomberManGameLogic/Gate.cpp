//
// Created by rojones on 2017/08/09.
//

#include "Gate.hpp"

Gate::Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model) :
		Entity(position, rotation, scale, model), _active(false)
{}

Gate::Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox) :
		Entity(position, rotation, scale, model, hitBox), _active(false)
{}

bool Gate::isActive() const
{
	return _active;
}

void Gate::actervate()
{
	_active = true;
}

bool Gate::isDamage() const {
	return _damage;
}

void Gate::setDamage(bool _damage) {
	Gate::_damage = _damage;
}

void Gate::damage(size_t damageCycles) {
	_damageCycels = damageCycles;
	_damage = true;
}

bool Gate::update() {
	std::cout << "gate updated\n";
	if (_damageCycels > 1)
		_damage = false;
	if (_damageCycels > 0)
		_damageCycels--;
	return true;
}
