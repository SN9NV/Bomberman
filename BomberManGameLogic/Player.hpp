#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include "Being.h"
#include "../io/InputManager.hpp"

class Player : public Being
{
public:
	Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed);
	void update(const cge::InputManager &input, unsigned lastFrameTime);

};

#endif //BOMBERMAN_PLAYER_HPP
