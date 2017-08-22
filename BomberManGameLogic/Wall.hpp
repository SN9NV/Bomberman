//
// Created by Robert JONES on 2017/08/11.
//

#ifndef BOMBERMAN_WALL_H
#define BOMBERMAN_WALL_H


#include "../entites/Entity.hpp"

class Wall : public cge::Entity
{
public:
	Wall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader);
	Wall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBoxRadius);
};


#endif //BOMBERMAN_WALL_H
