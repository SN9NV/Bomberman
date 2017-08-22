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
	float _ticks;

	void	_setEffects();

public:
	int getBombradius() const;
	virtual ~Bomb();
	Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, int _bombradius);
	Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader,float hitBox, int _bombradius);
	bool update(const cge::InputManager &input, unsigned lastFrameTime);
	bool isDeternate();
};


#endif //BOMBERMAN_BOMP_HPP
