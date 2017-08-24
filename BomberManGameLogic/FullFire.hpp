//
// Created by Owen EXALL on 2017/08/22.
//

#ifndef BOMBERMAN_FULLFIRE_HPP
#define BOMBERMAN_FULLFIRE_HPP


#include "PowerUPAbstract.hpp"

class FullFire : public PowerUPAbstract {
public:
	FullFire(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);

private:
	int _prevDamage;
};


#endif //BOMBERMAN_FULLFIRE_HPP
