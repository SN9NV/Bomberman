//
// Created by Robert JONES on 2017/08/07.
//

#include "Object.h"


Object::~Object()
{
}

float Object::getXLoc() const
{
	return xLoc;
}

void Object::setXLoc(float xLoc)
{
	Object::xLoc = xLoc;
}

float Object::getYLoc() const
{
	return yLoc;
}

void Object::setYLoc(float yLoc)
{
	Object::yLoc = yLoc;
}

Object::Object(float xLoc, float yLoc, std::string &modelPath, std::string &texturPath, cge::Loader loader) : xLoc(xLoc),
																											yLoc(yLoc)
{
	moddel = cge::Model(modelPath, texturPath, loader);
}

