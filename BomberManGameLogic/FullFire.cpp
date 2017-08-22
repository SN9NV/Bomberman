//
// Created by Owen EXALL on 2017/08/22.
//

#include "FullFire.hpp"

FullFire::FullFire(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
				   float hitBoxRadius) : PowerUPInterface(position, rotation, scale, model, hitBoxRadius) {}

void FullFire::Powerup(Player &player) {
	this->_prevDamage = player.getDamage();
	this->_active = true;
	player.setDamage(5);
}

void FullFire::Reverse(Player &player) {
	this->_active = false;
	player.setDamage(this->_prevDamage);
}

bool FullFire::isActive() {
	return (this->_active);
}
