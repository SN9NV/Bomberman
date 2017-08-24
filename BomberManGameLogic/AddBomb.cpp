//
// Created by Robert JONES on 2017/08/22.
//

#include "AddBomb.hpp"

AddBomb::AddBomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
				 cge::Loader &loader, float hitBoxRadius) :
		PowerUPAbstract(position, rotation, scale, model, loader, hitBoxRadius) {

}

void AddBomb::Powerup(Player &player) {
	player.setMaxBomb(player.getMaxBomb() + 1);
}

void AddBomb::Reverse(Player &player) {
	player.setMaxBomb(player.getMaxBomb() - 1);
}
