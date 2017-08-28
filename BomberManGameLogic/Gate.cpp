//
// Created by rojones on 2017/08/09.
//

#include "Gate.hpp"

Gate::Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius) :
		Entity(position, rotation, scale, model, loader, hitBoxRadius),
		_active(false),
		_damage(false),
		_damageCycles(0)
{
//this->_setEffects();
}


bool Gate::isActive() const
{
	return _active;
}

void Gate::activate()
{
	//this->playEffect("activate");
	_active = true;
}

bool Gate::isDamage() const {
	return _damage;
}

void Gate::setDamage(bool damage) {
	Gate::_damage = damage;
}

void Gate::damage(size_t damageCycles) {
	_damageCycles = damageCycles;
	_damage = true;
}

bool Gate::update() {
	if (_damageCycles == 1)
		_damage = false;
	if (_damageCycles > 0)
	{
		_damageCycles--;
	}
	return true;
}

/*
void Gate::_setEffects() {
	this->addNewSoundEffect("activate", "resources/audio/Activation.wav");
}
*/
