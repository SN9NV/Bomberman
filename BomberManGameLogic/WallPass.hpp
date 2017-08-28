//
// Created by rojones on 2017/08/26.
//

#ifndef BOMBERMAN_WALLPASS_HPP
#define BOMBERMAN_WALLPASS_HPP


#include "PowerUPAbstract.hpp"

class WallPass : public PowerUPAbstract
{
protected:
	bool _previusState;

public:
	WallPass(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader,
			 float hitBoxRadius);

	void Powerup(Player &player);
	void Reverse(Player &player);
};


#endif //BOMBERMAN_WALLPASS_HPP
