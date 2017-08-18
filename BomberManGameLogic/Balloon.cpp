//
// Created by rojones on 2017/08/09.
//

#include "Balloon.hpp"

std::uniform_int_distribution<int> _ndisision(0,1);
std::default_random_engine gen;

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model)
		: Being(position, rotation, scale, model, 0.002f)
{

}

Balloon::Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox)
		: Being(position, rotation, scale, model, hitBox, 0.002f)
{

}

bool Balloon::update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime)
{
	static int changeDir = 0;
	if ((_n_moveDir.x == 0 && _n_moveDir.z == 0) || (changeDir == 1000))
	{
		if (_ndisision(gen) == 1)
			_n_moveDir.x = (_ndisision(gen) == 1) ? -1 : 1;
		else
			_n_moveDir.z = (_ndisision(gen) == 1) ? -1 : 1;
	}
	changeDir = (changeDir == 1000) ? 0 : changeDir + 1;
	if (lastFrameTime < 500)
		return (Being::update(input, shader, lastFrameTime));
	return (true);
}
