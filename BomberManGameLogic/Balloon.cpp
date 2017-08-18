//
// Created by rojones on 2017/08/09.
//

#include "Balloon.hpp"

std::uniform_int_distribution<int> _ndist(0,1);
std::default_random_engine gen;

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model)
		: Being(position, rotation, scale, model, 0.002f)
{

}

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox)
		: Being(position, rotation, scale, model, hitBox, 0.002f)
{

}

bool Balloon::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	srand((unsigned int) time(NULL));
	if (_n_moveDir.x == 0 && _n_moveDir.z == 0)
	{
		/*if (rand() % 2 == 1)
			_n_moveDir.x = (rand() % 3) - 1;
		else
			_n_moveDir.z = (rand() % 3) - 1;*/
		if (_ndist(gen) == 1)
			_n_moveDir.x = (_ndist(gen) == 1) ? -1 : 1;
		else
			_n_moveDir.z = (_ndist(gen) == 1) ? -1 : 1;
	}
	if (lastFrameTime < 500)
		return (Being::update(input, lastFrameTime));
	return (true);
}
