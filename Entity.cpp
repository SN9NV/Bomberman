#include "Entity.hpp"
#include "Maths.hpp"

namespace cge {
	Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, const Model &model) :
			_model(model),
			_position(position),
			_rotation(rotation),
			_scale(scale),
			_transformation(1.0),
			_transformationLocation(0),
			_needsTransformationUpdate(true)
	{
		std::cout << "Using model at address: " << &model << "\n";
	}

	void Entity::addPosition(const glm::vec3 &delta) {
		this->_position += delta;
		this->_needsTransformationUpdate = true;
	}

	void Entity::setPosition(const glm::vec3 &position) {
		this->_position = position;
		this->_needsTransformationUpdate = true;
	}

	void Entity::addRotation(const glm::vec3 &delta) {
		this->_rotation += delta;
		this->_needsTransformationUpdate = true;
	}

	void Entity::setRotation(const glm::vec3 &rotation) {
		this->_rotation = rotation;
		this->_needsTransformationUpdate = true;
	}

	Model &Entity::getModel() {
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

	void Entity::update(const InputManager &input, unsigned lastFrameTime) {
		(void)input;
		(void)lastFrameTime;
	}
}