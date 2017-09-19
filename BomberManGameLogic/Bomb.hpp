//
// Created by rojones on 2017/08/08.
//

#ifndef BOMBERMAN_BOMP_HPP
#define BOMBERMAN_BOMP_HPP


#include "../entites/Entity.hpp"

class Bomb :public  cge::Entity
{
private:
	int _bombRadius;
	float _ticks;
	bool _isDetonate;

	void	_setEffects();

public:
	Bomb(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, int bombRadius = 3, float ticks = 1500, float hitBox = 0.0f);
	virtual ~Bomb();

	int getBombradius() const;
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
	bool isDeternate();

	bool isIsDetonate() const;

	void setDetonate(bool _isDetonate);
};


#endif //BOMBERMAN_BOMP_HPP
