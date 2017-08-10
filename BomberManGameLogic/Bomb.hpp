//
// Created by rojones on 2017/08/08.
//

#ifndef BOMBERMAN_BOMP_HPP
#define BOMBERMAN_BOMP_HPP


#include "../entites/Entity.hpp"

class Bomb :public  cge::Entity
{
private:
	int _bombradius;
public:
	int getBombradius() const;

private:
	float _ticks;
public:
	Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, int _bombradius);
	Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, glm::vec3 hitBox, int _bombradius);
	void update(const cge::InputManager &input, unsigned lastFrameTime);
	bool isDeternate();
};


#endif //BOMBERMAN_BOMP_HPP
