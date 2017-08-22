//
// Created by rojones on 2017/08/19.
//

#ifndef BOMBERMAN_POWERUPINTERFACE_HPP
#define BOMBERMAN_POWERUPINTERFACE_HPP

#include "../entites/Entity.hpp"
#include "Player.hpp"

class PowerUPInterface : public cge::Entity
{
public:
	PowerUPInterface(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius) :
			Entity(position, rotation, scale, model, loader, hitBoxRadius) {}

	virtual void Powerup(Player &player) = 0;
};

#endif //BOMBERMAN_POWERUPINTERFACE_HPP
