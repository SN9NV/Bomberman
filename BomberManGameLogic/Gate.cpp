//
// Created by rojones on 2017/08/09.
//

#include "Gate.hpp"

Gate::Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model) :
		Entity(position, rotation, scale, model), _active(false)
{}

Gate::Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, glm::vec3 hitBox) :
		Entity(position, rotation, scale, model, hitBox), _active(false)
{}

bool Gate::isActive() const
{
	return _active;
}

void Gate::actervate()
{
	_active = true;
}
