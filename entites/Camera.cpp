#include "Camera.hpp"
#include "../extras/Maths.hpp"

cge::Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const Window &window) :
		_position(position),
		_rotation(rotation),
		_projectionMatrix(
				glm::perspectiveFov<float>(FOV, window.getWidth(), window.getHeight(), NEAR_PLANE, FAR_PLANE)),
		_viewMatrix(1.0f),
		_needsUpdate(true),
		_track(nullptr),
		_trackOffset(1.0f),
		_trackOldPosition(0.0f) {

}

void cge::Camera::update() {
	glm::vec3 trackingPosition;

	if (this->_track != nullptr) {
		trackingPosition = this->_track->getPosition();
	}


	if (this->_track != nullptr) {
		this->_viewMatrix = glm::lookAt(trackingPosition + this->_trackOffset, trackingPosition, {0, 1, 0});
	} else {
		this->_viewMatrix = cge::Maths::createViewMatrix(*this);
	}


	if (this->_track != nullptr) {
		this->_trackOldPosition = trackingPosition;
	}
}

void cge::Camera::update(const cge::GLSLProgram &shader) {
	glm::vec3 trackingPosition;

	if (this->_track != nullptr) {
		trackingPosition = this->_track->getPosition();
	}

	if (this->_needsUpdate || (this->_track != nullptr && this->_trackOldPosition != trackingPosition)) {

		if (this->_track != nullptr) {
			this->_viewMatrix = glm::lookAt(trackingPosition + this->_trackOffset, trackingPosition, {0, 1, 0});
		} else {
			this->_viewMatrix = cge::Maths::createViewMatrix(*this);
		}

		this->_needsUpdate = false;

		if (this->_track != nullptr) {
			this->_trackOldPosition = trackingPosition;
		}
	}

	/// projectionMatrix * viewMatrix
	shader.uploadMatrix4f(
			shader.getUniformLocation("view"),
			this->_projectionMatrix * this->_viewMatrix
	);
}

void cge::Camera::setPosition(const glm::vec3 &position) {
	this->_position = position;
	this->_needsUpdate = true;
}

void cge::Camera::setRotation(const glm::vec3 &rotation) {
	this->_rotation = rotation;
	this->_needsUpdate = true;
}

void cge::Camera::addPosition(const glm::vec3 &delta) {
	this->_position += delta;
	this->_needsUpdate = true;
}

void cge::Camera::addRotation(const glm::vec3 &delta) {
	this->_rotation += delta;
	this->_needsUpdate = true;
}


glm::vec3 cge::Camera::getPosition() const {
	return this->_position;
}

glm::vec3 cge::Camera::getRotation() const {
	return this->_rotation;
}

glm::mat4 cge::Camera::getProjectionMatrix() const {
	return this->_projectionMatrix;
}

glm::mat4 cge::Camera::getViewMatrix() const {
	return this->_viewMatrix;
}

void cge::Camera::lookAt(const glm::vec3 &lookAtPos) {
	this->_viewMatrix = glm::lookAt(this->_position, lookAtPos, {0, 1, 0});
	this->_needsUpdate = true;
}

void cge::Camera::setTrackEntity(cge::Entity &entity) {
	this->_track = &entity;
	this->_needsUpdate = true;
}

void cge::Camera::setTrackOffset(const glm::vec3 &trackOffset) {
	this->_trackOffset = trackOffset;
	this->_needsUpdate = true;
}