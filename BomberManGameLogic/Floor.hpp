//
// Created by Robert JONES on 2017/08/28.
//

#ifndef BOMBERMAN_FLOOR_HPP
#define BOMBERMAN_FLOOR_HPP


#include "../entites/Entity.hpp"

class Floor : public cge::Entity{
public:
	Floor(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader,
		  float hitBoxRadius);
};


#endif //BOMBERMAN_FLOOR_HPP
