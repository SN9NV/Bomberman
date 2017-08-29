//
// Created by rojones on 2017/08/09.
//

#ifndef BOMBERMAN_BALLOON_HPP
#define BOMBERMAN_BALLOON_HPP


#include "Being.hpp"
#include <random>

class Balloon : public  Being {
public:
	Balloon(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, float hitBox = 0.5f);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime) override;

private:
	int _changeDir;
protected:
	void	_setEffects() override;
};


#endif //BOMBERMAN_BALLOON_HPP
