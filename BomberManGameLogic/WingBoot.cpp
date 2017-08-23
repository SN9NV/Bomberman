//
// Created by Owen EXALL on 2017/08/22.
//

#include "WingBoot.hpp"

WingBoot::WingBoot(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius) :
		PowerUPAbstract(position, rotation, scale, model, loader, hitBoxRadius)
{

}

void WingBoot::Powerup(Player &player) {
	player.setSpeed(player.getSpeed() + 0.001f);
	player.setAnimationSpeed((float)player.getAnimationSpeed() + 0.2f);
}

void WingBoot::Reverse(Player &player) {
	player.setSpeed(player.getSpeed() - 0.001f);
	player.setAnimationSpeed((float)player.getAnimationSpeed() - 0.2f);
}