//
// Created by rojones on 2017/08/19.
//

#ifndef BOMBERMAN_FIREUP_HPP
#define BOMBERMAN_FIREUP_HPP


#include "PowerUPAbstract.hpp"

class FireUp : public PowerUPAbstract
{
public:
	FireUp(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
};


#endif //BOMBERMAN_FIREUP_HPP
