//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_FIREDOWN_HPP
#define BOMBERMAN_FIREDOWN_HPP


#include "PowerUPAbstract.hpp"

class FireDown : public PowerUPAbstract {
public:
	FireDown(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
};


#endif //BOMBERMAN_FIREDOWN_HPP
