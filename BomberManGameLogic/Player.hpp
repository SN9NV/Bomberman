#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include "Being.h"
#include "../io/InputManager.hpp"
#include "Bomb.hpp"

class Player : public Being
{
private:
	int _lives;
public:
	int getLives() const;
	Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed);
	Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, glm::vec3 hitbox, float speed);
	void update(const cge::InputManager &input, unsigned lastFrameTime);
	int loseLife();


};

#endif //BOMBERMAN_PLAYER_HPP
