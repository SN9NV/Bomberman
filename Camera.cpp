#include <SDL_keycode.h>
#include "Camera.hpp"

void Camera::setPosition(const glm::vec3 &position) {
	this->_position = position;
}

void Camera::setRotation(const glm::vec3 &rotation) {
	this->_rotation = rotation;
}

Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation) :
	_position(position),
	_rotation(rotation)
{

}

void Camera::update(const InputManager &inputManager) {
	if (inputManager.isKeyPressed(SDLK_w)) {
		this->_position.y += 0.02f;
	}

	if (inputManager.isKeyPressed(SDLK_s)) {
		this->_position.y -= 0.02f;
	}

	if (inputManager.isKeyPressed(SDLK_d)) {
		this->_position.x += 0.02f;
	}

	if (inputManager.isKeyPressed(SDLK_a)) {
		this->_position.x -= 0.02f;
	}
}

glm::vec3 Camera::getPosition() const {
	return this->_position;
}

glm::vec3 Camera::getRotation() const {
	return this->_rotation;
}
