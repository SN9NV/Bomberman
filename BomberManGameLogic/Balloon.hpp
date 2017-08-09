//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_BALLOON_HPP
#define BOMBERMAN_BALLOON_HPP


#include "Being.h"

class Balloon : public  Being
{

public:
	Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model);
	void update(const cge::InputManager &input, unsigned lastFrameTime);
};


#endif //BOMBERMAN_BALLOON_HPP
