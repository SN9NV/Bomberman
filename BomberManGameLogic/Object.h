//
// Created by Robert JONES on 2017/08/07.
//

#ifndef BOMBERMAN_OBJECTS_H
#define BOMBERMAN_OBJECTS_H


#include "../Model.hpp"

class Object
{
public:
	virtual ~Object();

	float getXLoc() const;

	void setXLoc(float xLoc);

	float getYLoc() const;

	void setYLoc(float yLoc);

	Object(float xLoc, float yLoc, std::string &modelPath, std::string &texturPath, cge::Loader loader);

protected:
	float xLoc;
	float yLoc;
	cge::Model moddel;
};


#endif //BOMBERMAN_OBJECTS_H
