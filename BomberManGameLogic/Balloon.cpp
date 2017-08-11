//
// Created by rojones on 2017/08/09.
//

#include "Balloon.hpp"

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model)
		: Being(position, rotation, scale, model, 0.002f)
{

}

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox)
		: Being(position, rotation, scale, model, hitBox, 0.002f)
{

}

void Balloon::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	srand((unsigned int) time(NULL));
	if (_n_moveDir.x == 0 && _n_moveDir.z == 0)
	{
		if (rand() % 2 == 1)
			_n_moveDir.x = (rand() % 3) - 1;
		else
			_n_moveDir.z = (rand() % 3) - 1;
	}
	if (lastFrameTime < 500)
		Being::update(input, lastFrameTime);
}
