//
// Created by Robert JONES on 2017/08/11.
//

#include "Wall.hpp"

Wall::Wall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius)
		: Entity(position, rotation, scale, model, loader, hitBoxRadius) {}
