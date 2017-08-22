//
// Created by rojones on 2017/08/19.
//

#include "FireUp.hpp"

FireUp::FireUp(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius)
		: PowerUPAbstract(position, rotation, scale, model, loader, hitBoxRadius) {}

void FireUp::Powerup(Player &player)
{
	if (player.getDamage() < 5)
		player.setDamage(player.getDamage() + 1);
}

void FireUp::Reverse(Player &player) {
		if (player.getDamage() > 2)
			player.setDamage(player.getDamage() - 1);
}

