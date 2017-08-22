//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_WINGBOOT_HPP
#define BOMBERMAN_WINGBOOT_HPP


#include "PowerUPInterface.hpp"

class WingBoot : public PowerUPInterface {
	WingBoot(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
	bool isActive();
};


#endif //BOMBERMAN_WINGBOOT_HPP
