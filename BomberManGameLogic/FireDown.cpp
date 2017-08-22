//
// Created by Owen EXALL on 2017/08/22.
//

#include "FireDown.hpp"

FireDown::FireDown(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius) :
	PowerUPAbstract(position, rotation, scale, model, hitBoxRadius) {}

void FireDown::Powerup(Player &player) {
	if (player.getDamage() > 2)
		player.setDamage(player.getDamage() - 1);
}

void FireDown::Reverse(Player &player) {
		if (player.getDamage() < 5)
			player.setDamage(player.getDamage() + 1);
}

