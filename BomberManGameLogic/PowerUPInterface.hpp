//
// Created by rojones on 2017/08/19.
//

#ifndef BOMBERMAN_POWERUPINTERFACE_HPP
#define BOMBERMAN_POWERUPINTERFACE_HPP

#include "../entites/Entity.hpp"
#include "Player.hpp"

class PowerUPInterface : public cge::Entity
{
protected:
	bool _active;

public:
	PowerUPInterface(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model,
					 float hitBoxRadius) : Entity(position, rotation, scale, model, hitBoxRadius) {}
	virtual void Powerup(Player &player) = 0;
	virtual void Reverse(Player &player) = 0;
	virtual bool isActive() = 0;
};

#endif //BOMBERMAN_POWERUPINTERFACE_HPP
