#include <SDL_keycode.h>
#include "Camera.hpp"
#include "Maths.hpp"

std::ostream &operator<<(std::ostream &out, const glm::mat4 &rhs);

Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const Window &window) :
	_position(position),
	_rotation(rotation),
	_projectionMatrix(glm::perspectiveFov<float>(FOV, window.getWidth(), window.getHeight(), NEAR_PLANE, FAR_PLANE)),
	_viewMatrix(1.0f),
	_needsUpdate(true)
{

}

void Camera::update(const InputManager &inputManager, const GLSLProgram &shader, bool printCameraChange) {
	if (inputManager.isKeyPressed(SDLK_w)) {
		this->_position.y += 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_s)) {
		this->_position.y -= 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_d)) {
		this->_position.x += 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_a)) {
		this->_position.x -= 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_q)) {
		this->_position.z += 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_e)) {
		this->_position.z -= 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_UP)) {
		this->_rotation.x += 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_DOWN)) {
		this->_rotation.x -= 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_LEFT)) {
		this->_rotation.y -= 0.02f;
		this->_needsUpdate = true;
	}

	if (inputManager.isKeyPressed(SDLK_RIGHT)) {
		this->_rotation.y += 0.02f;
		this->_needsUpdate = true;
	}

	if (this->_needsUpdate) {
		if (printCameraChange) {
			std::cout << *this << "\n";
		}

		this->_viewMatrix = Maths::createViewMatrix(*this);

//		projectionMatrix * viewMatrix
		shader.uploadMatrix4f(
				shader.getUniformLocation("view"),
				this->_projectionMatrix * this->_viewMatrix
		);

		this->_needsUpdate = false;
	}
}

void Camera::setPosition(const glm::vec3 &position) {
	this->_position = position;
	this->_needsUpdate = true;
}

void Camera::setRotation(const glm::vec3 &rotation) {
	this->_rotation = rotation;
	this->_needsUpdate = true;
}

glm::vec3 Camera::getPosition() const {
	return this->_position;
}

glm::vec3 Camera::getRotation() const {
	return this->_rotation;
}

glm::mat4 Camera::getProjectionMatrix() const {
	return this->_projectionMatrix;
}

glm::mat4 Camera::getViewMatrix() const {
	return this->_viewMatrix;
}

std::ostream &operator<<(std::ostream &out, const Camera &rhs) {
	glm::vec3 position = rhs.getPosition();
	glm::vec3 rotation = rhs.getRotation();

	out << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
	out << "Rotation: (" << rotation.x << ", " << rotation.y << ", " << rotation.z << ")";

	return out;
}