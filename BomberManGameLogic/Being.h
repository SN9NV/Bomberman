//
// Created by Robert JONES on 2017/08/07.
//

#ifndef BOMBERMAN_BEING_H
#define BOMBERMAN_BEING_H


#include "Object.h"
#include <glm/glm.hpp>

class Being : public Object
{
private:
	float	speed;
	glm::vec2	movement;
public:
	Being(float xLoc, float yLoc, std::string &modelPath, std::string &texturPath, cge::Loader &loader, float speed);
	void update();

};


#endif //BOMBERMAN_BEING_H
