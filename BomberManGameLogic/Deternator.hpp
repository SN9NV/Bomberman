//
// Created by Robert JONES on 2017/08/24.
//

#ifndef BOMBERMAN_DETERNATOR_HPP
#define BOMBERMAN_DETERNATOR_HPP


#include "PowerUPAbstract.hpp"

class Deternator  : public PowerUPAbstract{
public:
	Deternator(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius);
	void Powerup(Player &player);
	void Reverse(Player &player);
};


#endif //BOMBERMAN_DETERNATOR_HPP
