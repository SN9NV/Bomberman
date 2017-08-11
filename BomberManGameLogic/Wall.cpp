//
// Created by Robert JONES on 2017/08/11.
//

#include "Wall.h"

Wall::Wall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model) : Entity(position,
																										  rotation,
																										  scale, model)
{}

Wall::Wall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBoxRadius)
		: Entity(position, rotation, scale, model, hitBoxRadius)
{}
