#include "Entity.hpp"

Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, const tinygltf::Model &model) :
	_model(model),
	_position(position),
	_rotation(rotation),
	_scale(scale)
{

}

void Entity::addPosition(const glm::vec3 &delta) {
	this->_position += delta;
}

void Entity::setPosition(const glm::vec3 &position) {
	this->_position = position;
}

void Entity::addRotation(const glm::vec3 &delta) {
	this->_rotation += delta;
}

void Entity::setRotation(const glm::vec3 &rotation) {
	this->_rotation = rotation;
}

const tinygltf::Model &Entity::getModel() const {
	return this->_model;
}

glm::vec3 Entity::getPosition() const {
	return this->_position;
}

glm::vec3 Entity::getRotation() const {
	return this->_rotation;
}

float Entity::getScale() const {
	return this->_scale;
}
