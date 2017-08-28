//
// Created by Robert JONES on 2017/08/24.
//

#include "Deternator.hpp"

void Deternator::Powerup(Player &player) {
player.setBombTime(10000);
	player.setDetonator(true);
}

void Deternator::Reverse(Player &player) {
	player.setBombTime(1500);
	player.setDetonator(false);
}

Deternator::Deternator(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
					   cge::Loader &loader, float hitBoxRadius) : PowerUPAbstract(position, rotation, scale, model,
																				  loader, hitBoxRadius) {

}

