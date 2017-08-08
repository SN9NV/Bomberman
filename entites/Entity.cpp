#include "Entity.hpp"
#include "../extras/Maths.hpp"

cge::Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model) :
		_model(model),
		_position(position),
		_rotation(rotation),
		_scale(scale),
		_transformation(1.0),
		_transformationLocation(0),
		_needsTransformationUpdate(true)
{

}

void cge::Entity::addPosition(const glm::vec3 &delta) {
	this->_position += delta;
	this->_needsTransformationUpdate = true;
}

void cge::Entity::setPosition(const glm::vec3 &position) {
	this->_position = position;
	this->_needsTransformationUpdate = true;
}

void cge::Entity::addRotation(const glm::vec3 &delta) {
	this->_rotation += delta;
	this->_needsTransformationUpdate = true;
}

void cge::Entity::setRotation(const glm::vec3 &rotation) {
	this->_rotation = rotation;
	this->_needsTransformationUpdate = true;
}

cge::Model &cge::Entity::getModel() {
	return this->_model;
}

glm::vec3 cge::Entity::getPosition() const {
	return this->_position;
}

glm::vec3 cge::Entity::getRotation() const {
	return this->_rotation;
}

float cge::Entity::getScale() const {
	return this->_scale;
}

void cge::Entity::update(const cge::InputManager &input, unsigned lastFrameTime) {
	(void)input;
	(void)lastFrameTime;
}