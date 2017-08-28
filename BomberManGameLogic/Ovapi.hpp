//
// Created by rojones on 2017/08/25.
//

#ifndef BOMBERMAN_OVAPI_HPP
#define BOMBERMAN_OVAPI_HPP


#include "Being.hpp"
#include "Player.hpp"

class Ovapi : public Being
{
private:
	int _changeDir;
	const Player& _player;
	std::vector<std::vector<cge::Entity *>> &_level;

public:
	Ovapi(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, cge::Loader &loader, const Player& player, std::vector<std::vector<cge::Entity *>> &level, float hitBox = 0.5f);
	bool update(const cge::InputManager &input, cge::GLSLProgram &shader, unsigned lastFrameTime);
};


#endif //BOMBERMAN_OVAPI_HPP
