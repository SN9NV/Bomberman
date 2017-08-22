//
// Created by Robert JONES on 2017/08/22.
//

#ifndef BOMBERMAN_ADDBOMB_HPP
#define BOMBERMAN_ADDBOMB_HPP


#include "PowerUPAbstract.hpp"

class AddBomb : public PowerUPAbstract{
public:
	AddBomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
};


#endif //BOMBERMAN_ADDBOMB_HPP
