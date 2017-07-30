#include "Camera.hpp"

Camera::Camera() :
	_screenWidth(0),
	_screenHeight(0),
	_bNeedsMatrixUpdate(true),
	_scale(1.0f),
	_position(0.0f, 0.0f, 0.0f),
	_cameraMatrix(1.0f),
	_orthoMatrix(1.0f)
{

}

void Camera::init(unsigned screenWidth, unsigned screenHeight)
{
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;

	this->_orthoMatrix = glm::ortho(
			0.0f,
			static_cast<float>(this->_screenWidth),
			0.0f,
			static_cast<float>(this->_screenHeight));
}

void Camera::update()
{
	if (this->_bNeedsMatrixUpdate) {
		glm::vec3	translate(-this->_position.x + this->_screenWidth/2.0f, -this->_position.y + this->_screenHeight/2.0f, 0.0f);
		glm::vec3	scale(this->_scale, this->_scale, 0.0f);

		this->_cameraMatrix = glm::translate(this->_orthoMatrix, translate);
		this->_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * this->_cameraMatrix;

		this->_bNeedsMatrixUpdate = false;
	}
}

void Camera::addScale(const float delta)
{
	this->_scale += delta;
	this->_bNeedsMatrixUpdate = true;
}

void Camera::addPosition(const glm::vec3 &delta)
{
	this->_position += delta;
	this->_bNeedsMatrixUpdate = true;
}

void Camera::setPosition(const glm::vec3 &position)
{
	this->_position = position;
	this->_bNeedsMatrixUpdate = true;
}

void Camera::addRotation(const glm::vec3 &delta)
{
	this->_rotation += delta;
	this->_bNeedsMatrixUpdate = true;
}

void Camera::setRotation(const glm::vec3 &rotation)
{
	this->_rotation = rotation;
	this->_bNeedsMatrixUpdate = true;
}

void Camera::setScale(const float scale)
{
	this->_scale = scale;
	this->_bNeedsMatrixUpdate = true;
}

void Camera::setCameraMatrix(const glm::mat4 &cameraMatrix)
{
	this->_cameraMatrix = cameraMatrix;
	this->_bNeedsMatrixUpdate = true;
}

glm::vec3 Camera::position() const
{
	return this->_position;
}

float Camera::scale() const
{
	return this->_scale;
}

glm::mat4 Camera::cameraMatrix() const
{
	return this->_cameraMatrix;
}

glm::vec3 Camera::screenToWorldCoords(glm::vec2 screenCoords) const
{
	screenCoords.y = this->_screenHeight - screenCoords.y;

	screenCoords -= glm::vec3(this->_screenWidth / 2.0f, this->_screenHeight / 2.0f, 0.0f);
	screenCoords /= this->_scale;
	screenCoords += this->_position;

	return screenCoords;
}

