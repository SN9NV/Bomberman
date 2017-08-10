//
// Created by rojones on 2017/08/09.
//

#include "DestructWall.hpp"

DestructWall::DestructWall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model)
		: Entity(position, rotation, scale, model) {}

DestructWall::DestructWall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, glm::vec3 hitBox)
		: Entity(position, rotation, scale, model, hitBox) {}
