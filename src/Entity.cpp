#include "Entity.hpp"

Entity::Entity() :
	_model(),
	_position(0.0f, 0.0f, 0.0f),
	_rotation(0.0f, 0.0f, 0.0f),
	_scale(1.0f)
{

}

Entity::Entity(Model &model, glm::vec3 &position, glm::vec3 &rotation, float scale) :
	_model(model),
	_position(position),
	_rotation(rotation),
	_scale(scale)
{

}

Entity::Entity(Entity &entity)
{
	*this = entity;
}

Entity::~Entity()
{

}

Entity &Entity::operator=(Entity &rhs)
{
	this->_model = rhs._model;
	this->_position = rhs._position;
	this->_rotation = rhs._rotation;
	this->_scale = rhs._scale;

	return *this;
}

Entity::init(Model &model, glm::vec3 &position, glm::vec3 &rotation, float scale)
{
	this->_model = model;
	this->_position = position;
	this->_rotation = rotation;
	this->_scale = scale;
}

void Entity::addPosition(glm::vec3 &delta)
{
	this->_position += delta;
}

void Entity::addRotation(glm::vec3 &delta)
{
	this->_rotation += delta;
}

void Entity::addScale(float delta)
{
	this->_scale += delta;
}

void Entity::setModel(Model &model)
{
	this->_model = model;
}

void Entity::setPosition(glm::vec3 &position)
{
	this->_position = position;
}

void Entity::setRotation(glm::vec3 &rotation)
{
	this->_rotation = rotation;
}

void Entity::setScale(float scale)
{
	this->_scale = scale;
}

Model Entity::model() const
{
	return this->_model;
}

glm::vec3 Entity::position() const
{
	return this->_position;
}

glm::vec3 Entity::rotation() const
{
	return this->_rotation;
}

float Entity::scale() const
{
	return this->_scale;
}
