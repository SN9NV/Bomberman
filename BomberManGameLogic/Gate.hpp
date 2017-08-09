//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_GATE_HPP
#define BOMBERMAN_GATE_HPP


#include "../entites/Entity.hpp"

class Gate : public cge::Entity
{
private:
	bool _active;
public:
	void actervate();
	bool isActive() const;
	Gate(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model);
};


#endif //BOMBERMAN_GATE_HPP
