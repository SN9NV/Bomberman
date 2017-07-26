#include "Camera2D.hpp"

Camera2D::Camera2D() :
	_screenWidth(0),
	_screenHeight(0),
	_bNeedsMatrixUpdate(true),
	_scale(1.0f),
	_position(0, 0),
	_cameraMatrix(1.0f),
	_orthoMatrix(1.0f)
{

}

Camera2D::~Camera2D()
{

}

void Camera2D::init(unsigned screenWidth, unsigned screenHeight)
{
	this->_screenWidth = screenWidth;
	this->_screenHeight = screenHeight;

	this->_orthoMatrix = glm::ortho(
			0.0f,
			static_cast<float>(this->_screenWidth),
			0.0f,
			static_cast<float>(this->_screenHeight));
}

void Camera2D::update()
{
	if (this->_bNeedsMatrixUpdate) {
		glm::vec3	translate(-this->_position.x + this->_screenWidth/2.0f, -this->_position.y + this->_screenHeight/2.0f, 0.0f);
		glm::vec3	scale(this->_scale, this->_scale, 0.0f);

		this->_cameraMatrix = glm::translate(this->_orthoMatrix, translate);
		this->_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * this->_cameraMatrix;

		this->_bNeedsMatrixUpdate = false;
	}
}

void Camera2D::addScale(float scale)
{
	this->_scale += scale;
	this->_bNeedsMatrixUpdate = true;
}

void Camera2D::addPosition(const glm::vec2 &rhs)
{
	this->_position += rhs;
	this->_bNeedsMatrixUpdate = true;
}

void Camera2D::setPosition(const glm::vec2 &position)
{
	this->_position = position;
	this->_bNeedsMatrixUpdate = true;
}

void Camera2D::setScale(float scale)
{
	this->_scale = scale;
	this->_bNeedsMatrixUpdate = true;
}

void Camera2D::setCameraMatrix(const glm::mat4 &cameraMatrix)
{
	this->_cameraMatrix = cameraMatrix;
	this->_bNeedsMatrixUpdate = true;
}

glm::vec2 Camera2D::getPosition() const
{
	return this->_position;
}

float Camera2D::getScale() const
{
	return this->_scale;
}

glm::mat4 Camera2D::getCameraMatrix() const
{
	return this->_cameraMatrix;
}

