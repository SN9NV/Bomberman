//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_WINGBOOT_HPP
#define BOMBERMAN_WINGBOOT_HPP


#include "PowerUPAbstract.hpp"

class WingBoot : public PowerUPAbstract {
public:
	WingBoot(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
};


#endif //BOMBERMAN_WINGBOOT_HPP
