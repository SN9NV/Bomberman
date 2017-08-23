//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_DESTRUCTWALL_HPP
#define BOMBERMAN_DESTRUCTWALL_HPP


#include "../entites/Entity.hpp"

class DestructWall : public cge::Entity {
public:
	DestructWall(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBox = 0.5f);
};


#endif //BOMBERMAN_DESTRUCTWALL_HPP
