//
// Created by Robert JONES on 2017/08/07.
//

#include "Being.h"

Being::Being(float xLoc, float yLoc, std::string &modelPath, std::string &texturPath, cge::Loader &loader, float speed)
		: Object(xLoc, yLoc, modelPath, texturPath, loader), speed(speed), movement(glm::vec2(0, 0))
{
	movement = glm::normalize(movement);
}

void Being::update()
{
	xLoc += speed * movement.x;
	yLoc += speed * movement.y;
}
