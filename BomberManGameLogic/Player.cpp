#include <SDL_keycode.h>
#include "Player.hpp"

void Player::update(const cge::InputManager &input, unsigned lastFrameTime)
{
	if (input.isKeyPressed(SDLK_w))
	{
		this->_n_moveDir.z = -1;
	}
	else if (input.isKeyPressed(SDLK_s))
		this->_n_moveDir.z = 1;
	else
		this->_n_moveDir.z = 0;

	if (input.isKeyPressed(SDLK_d))
		this->_n_moveDir.x = 1;
	else if (input.isKeyPressed(SDLK_a))
		this->_n_moveDir.x = -1;
	else
		this->_n_moveDir.x = 0;


	Being::update(input, lastFrameTime);
}

Player::Player(const glm::vec3 &position, const glm::vec3 &rotation, float scale, cge::Model &model, float speed)
		: Being(position, rotation, scale, model, speed)
{}
