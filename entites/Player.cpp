#include <SDL_keycode.h>
#include "Player.hpp"

void cge::Player::update(const cge::InputManager &input, unsigned lastFrameTime) {
	const float velocity = 0.002f * lastFrameTime;

	if (input.isKeyPressed(SDLK_w)) {
		this->_position.y += velocity;
	}

	if (input.isKeyPressed(SDLK_s)) {
		this->_position.y -= velocity;
	}

	if (input.isKeyPressed(SDLK_d)) {
		this->_position.x += velocity;
	}

	if (input.isKeyPressed(SDLK_a)) {
		this->_position.x -= velocity;
	}

	if (input.isKeyPressed(SDLK_q)) {
		this->_position.z += velocity;
	}

	if (input.isKeyPressed(SDLK_e)) {
		this->_position.z -= velocity;
	}
}