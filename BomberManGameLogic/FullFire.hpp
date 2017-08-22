//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_FULLFIRE_HPP
#define BOMBERMAN_FULLFIRE_HPP


#include "PowerUPInterface.hpp"

class FullFire : public PowerUPInterface {
public:
	FullFire(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
	bool isActive();
private:
	int _prevDamage;
};


#endif //BOMBERMAN_FULLFIRE_HPP
