//
// Created by rojones on 2017/08/19.
//

#include "FireUp.hpp"

FireUp::FireUp(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius)
		: PowerUPInterface(position, rotation, scale, model, hitBoxRadius) {}

void FireUp::Powerup(Player &player)
{
	if (player.getDamage() < 5)
		player.setDamage(player.getDamage() + 1);
	_active = true;
}

void FireUp::Reverse(Player &player) {
	if (_active) {
		_active = false;

		if (player.getDamage() > 2)
			player.setDamage(player.getDamage() - 1);
	}
}

bool FireUp::isActive() {
	return (_active);
}
