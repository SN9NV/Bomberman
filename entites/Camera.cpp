#include "Camera.hpp"
#include "../extras/Maths.hpp"
#include "../extras/glmOstream.hpp"
#include <glm/gtx/matrix_decompose.hpp>

std::ostream &operator<<(std::ostream &out, const glm::mat4 &rhs);

namespace cge
{
	Camera::Camera(const glm::vec3 &position, const glm::vec3 &rotation, const Window &window) :
			_position(position),
			_rotation(rotation),
			_projectionMatrix(
					glm::perspectiveFov<float>(FOV, window.getWidth(), window.getHeight(), NEAR_PLANE, FAR_PLANE)),
			_viewMatrix(1.0f),
			_needsUpdate(true),
			_track(nullptr),
			_trackOffset(1.0f),
			_trackOldPosition(0.0f)
	{

	}

	void Camera::update()
	{
//			this->_viewMatrix = Maths::createViewMatrix(*this);
	}

	void Camera::update(const GLSLProgram &shader, bool printCameraChange)
	{
		glm::vec3	trackingPosition;

		if (this->_track != nullptr) {
			this->_track->getPosition();
		}

		if (this->_needsUpdate || (this->_track != nullptr && this->_trackOldPosition != trackingPosition))
		{
			if (printCameraChange) {
				std::cout << *this << "\n";
			}

			if (this->_track != nullptr) {
				this->_viewMatrix = glm::lookAt(trackingPosition + this->_trackOffset, trackingPosition, { 0, 1, 0 });
			} else {
				this->_viewMatrix = Maths::createViewMatrix(*this);
			}

			/// projectionMatrix * viewMatrix
			shader.uploadMatrix4f(
					shader.getUniformLocation("view"),
					this->_projectionMatrix * this->_viewMatrix
			);

			this->_needsUpdate = false;

			if (this->_track != nullptr) {
				this->_trackOldPosition = trackingPosition;
			}
		}
	}

	void Camera::setPosition(const glm::vec3 &position)
	{
		this->_position = position;
		this->_needsUpdate = true;
	}

	void Camera::setRotation(const glm::vec3 &rotation)
	{
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


	glm::vec3 Camera::getPosition() const
	{
		return this->_position;
	}

	glm::vec3 Camera::getRotation() const
	{
		return this->_rotation;
	}

	glm::mat4 Camera::getProjectionMatrix() const
	{
		return this->_projectionMatrix;
	}

	glm::mat4 Camera::getViewMatrix() const
	{
		return this->_viewMatrix;
	}

	void Camera::lookAt(const glm::vec3 &lookAtPos) {
//		glm::vec3 lookAt = this->_position - lookAtPos;

		this->_viewMatrix = glm::lookAt(this->_position, lookAtPos, { 0, 0, -1 });

//		glm::quat rotation = glm::quat_cast(lookAt);
//
//		this->_rotation = glm::degrees(glm::eulerAngles(rotation));
//
//		this->_rotation = {
//			glm::atan(lookAt.y / lookAt.z),
//			0, 0
//			glm::atan(lookAt.z / lookAt.x),
//			glm::atan(lookAt.x / lookAt.y)
//		};
	}

	void Camera::setTrackEntity(cge::Entity &entity) {
		this->_track = &entity;
	}

	void Camera::setTrackOffset(const glm::vec3 &trackOffset) {
		this->_trackOffset = trackOffset;
	}
}

std::ostream &operator<<(std::ostream &out, const cge::Camera &rhs)
{
	glm::vec3 position = rhs.getPosition();
	glm::vec3 rotation = rhs.getRotation();

	out << "Position: (" << position.x << ", " << position.y << ", " << position.z << ")\n";
	out << "Rotation: (" << rotation.x << ", " << rotation.y << ", " << rotation.z << ")";

	return out;
}