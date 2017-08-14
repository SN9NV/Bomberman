#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include "Being.h"
#include "../io/InputManager.hpp"
#include "Bomb.hpp"

class Player : public Being
{
private:
	int _lives;
	int _up = SDLK_w;
	int _down = SDLK_s;
	int _left = SDLK_a;
	int _right = SDLK_d;
	int _bomb = SDLK_SPACE;


private:
	int _special = SDLK_v;
	int _menue = SDLK_ESCAPE;
	bool _pauseMenue;

public:

	bool isPauseMenue() const;
	void setPauseMenue(bool _pauseMenue);
	int getSpecial() const;
	void setSpecial(int _special);
	int getLives() const;
	Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed);
	Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float hitbox, float speed);
	bool update(const cge::InputManager &input, unsigned lastFrameTime);
	int loseLife();

};

#endif //BOMBERMAN_PLAYER_HPP
