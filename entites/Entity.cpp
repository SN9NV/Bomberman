#include "Entity.hpp"
#include "../extras/Maths.hpp"

namespace cge
{
	Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model) :
			_model(model),
			_position(position),
			_rotation(rotation),
			_scale(scale),
			_hitBox({0, 0, 0}),
			_transformation(1.0),
			_transformationLocation(0),
			_needsTransformationUpdate(true)
	{

	}

	Entity::Entity(const glm::vec3 &position, const glm::vec3 &rotation, float scale, Model &model, glm::vec3 hitBox) :
			_model(model),
			_position(position),
			_rotation(rotation),
			_scale(scale),
			_hitBox(hitBox * _scale),
			_transformation(1.0),
			_transformationLocation(0),
			_needsTransformationUpdate(true)
	{

	}

	void Entity::addPosition(const glm::vec3 &delta)
	{
		this->_position += delta;
		this->_needsTransformationUpdate = true;
	}

	void Entity::setPosition(const glm::vec3 &position)
	{
		this->_position = position;
		this->_needsTransformationUpdate = true;
	}

	void Entity::addRotation(const glm::vec3 &delta)
	{
		this->_rotation += delta;
		this->_needsTransformationUpdate = true;
	}

	void Entity::setRotation(const glm::vec3 &rotation)
	{
		this->_rotation = rotation;
		this->_needsTransformationUpdate = true;
	}

	Model &Entity::getModel()
	{
		return this->_model;
	}

	glm::vec3 Entity::getPosition() const
	{
		return this->_position;
	}

	glm::vec3 Entity::getRotation() const
	{
		return this->_rotation;
	}

	float Entity::getScale() const
	{
		return this->_scale;
	}

	void Entity::update(const cge::InputManager &input, unsigned lastFrameTime)
	{
		(void) lastFrameTime;
		(void) input;
	}

	glm::vec3 Entity::getHitBox() const
	{
		return _hitBox;
	}

	void Entity::setHitBox(const glm::vec3 &hitBox)
	{
		_hitBox = hitBox * _scale;

	}

	void Entity::setScale(float scale)
	{
		_scale = scale;
		this->_needsTransformationUpdate = true;
		_hitBox = _hitBox * _scale;
	}


}