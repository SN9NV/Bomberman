//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_BALLOON_HPP
#define BOMBERMAN_BALLOON_HPP


#include "Being.h"
#include <random>

class Balloon : public  Being
{
private:

public:
	Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model);
	Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitBox);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
};


#endif //BOMBERMAN_BALLOON_HPP
