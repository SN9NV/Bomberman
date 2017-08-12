#include "Player.hpp"

namespace cge {
	void Player::update(const InputManager &input, unsigned lastFrameTime) {
		const float velocity = 0.002f * lastFrameTime;

		if (input.isKeyPressed(GLFW_KEY_W)) {
			this->_position.y += velocity;
		}

		if (input.isKeyPressed(GLFW_KEY_S)) {
			this->_position.y -= velocity;
		}

		if (input.isKeyPressed(GLFW_KEY_D)) {
			this->_position.x += velocity;
		}

		if (input.isKeyPressed(GLFW_KEY_A)) {
			this->_position.x -= velocity;
		}

		if (input.isKeyPressed(GLFW_KEY_Q)) {
			this->_position.z += velocity;
		}

		if (input.isKeyPressed(GLFW_KEY_E)) {
			this->_position.z -= velocity;
		}
	}
}