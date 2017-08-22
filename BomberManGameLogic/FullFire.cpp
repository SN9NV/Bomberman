//
// Created by Owen EXALL on 2017/08/22.
//

#include "FullFire.hpp"

FullFire::FullFire(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius) :
		PowerUPAbstract(position, rotation, scale, model, loader, hitBoxRadius) {}

void FullFire::Powerup(Player &player) {
	this->_prevDamage = player.getDamage();
	player.setDamage(5);
}

void FullFire::Reverse(Player &player) {
	player.setDamage(this->_prevDamage);
}