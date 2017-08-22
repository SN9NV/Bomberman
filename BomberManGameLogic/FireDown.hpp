//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_FIREDOWN_HPP
#define BOMBERMAN_FIREDOWN_HPP


#include "PowerUPInterface.hpp"

class FireDown : public PowerUPInterface {
	FireDown(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
	bool isActive();
};


#endif //BOMBERMAN_FIREDOWN_HPP
