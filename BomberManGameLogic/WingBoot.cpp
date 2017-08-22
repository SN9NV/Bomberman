//
// Created by Owen EXALL on 2017/08/22.
//

#include "WingBoot.hpp"

WingBoot::WingBoot(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
				   float hitBoxRadius) : PowerUPInterface(position, rotation, scale, model, hitBoxRadius) {

}

void WingBoot::Powerup(Player &player) {
	this->_active = true;
	player.setSpeed(player.getSpeed() + 0.01f);
}

void WingBoot::Reverse(Player &player) {
	this->_active = false;
	player.setSpeed(player.getSpeed() - 0.01f);
}

bool WingBoot::isActive() {
	return (this->_active);
}
